#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    unsigned char c,s [100];
    int32_t i=0;
    while ((c = getchar())!= '.')
    {
       if(c > 64 && c < 91) 
          c += 32;   
       if(c!='.') 
          s[i++] = c;
    }
    s[i]='\0';
    printf("%s",s);
    
    return 0;
}
