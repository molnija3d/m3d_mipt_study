#include <stdio.h>
#include <inttypes.h>

#define ALPH 26

char cesar(char c, uint8_t n)
{
        uint8_t code = 0;
        code = (c + n) % ALPH;
        return code;
}

int main(void)
{
        char c = 0, b = 0;
        uint8_t n = 0;
        scanf("%" SCNu8, &n);
        while ( ( c = getchar() ) != '.' )
        {
               if ( c >= 'A' && c <= 'Z' )
               { 
                   b = cesar(c - 'A',n) + 'A';
                   putchar(b);
               }
               else if ( c >= 'a' && c <= 'z' )
               {
                   b = cesar(c - 'a',n) + 'a';
                   putchar(b);
               }
        }
        putchar('.');
        return 0;
}


