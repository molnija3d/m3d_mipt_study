#include <stdio.h>

int main(void)
{
    unsigned char c;
    while ((c = getchar())!= '.')
    {
       if(c > 64 && c < 91) 
          c += 32;
       putchar(c);
    }
    
    return 0;
}
