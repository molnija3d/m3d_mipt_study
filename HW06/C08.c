#include <stdio.h>

char ToUP(char c);

int main(void)
{
    char c;
    while ((c = getchar())!='.')
    {
       if(c > 0x60 && c < 0x7B) c = ToUP(c);
       putchar(c);
    }     
    putchar('\n');
    return 0;
}

char ToUP(char c)
{
    return  c-0x20;
}
