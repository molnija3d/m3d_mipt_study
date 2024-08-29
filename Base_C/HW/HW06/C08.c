#include <stdio.h>
/*
Составить функцию, которая переводит латинскую строчную букву в заглавную. И показать пример ее использования.
*/
char ToUP(char c);

int main(void)
{
    char c;
    while ((c = getchar())!='.')
    {
        if(c > 0x60 && c < 0x7B)
            c = ToUP(c);
        putchar(c);
    }
    putchar('\n');
    return 0;
}

char ToUP(char c)
{
    return  c-0x20;
}
