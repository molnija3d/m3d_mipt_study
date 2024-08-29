#include <stdio.h>
#include <inttypes.h>
/*
Составить логическую функцию, которая определяет, что текущий символ это цифра. Написать программу считающую количество цифр в тексте.
int is_digit(char c)
 */

int32_t is_digit(char c);


int main(void)
{
    char c;
    int32_t i=0;
    while((c=getchar())!='.')
    {
        if(is_digit(c))
            ++i;
    }
    printf("%"PRId32"\n",i);
    return 0;
}


int32_t is_digit(char c)
{
    if(c >= 0x30 && c <= 0x39)
        return 1;
    return 0;
}
