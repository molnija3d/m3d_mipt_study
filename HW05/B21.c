#include <stdio.h>
/*Дан текст состоящий из английских букв и цифр, заканчивается символом «.» Перевести все заглавные английские буквы в строчные.*/

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
