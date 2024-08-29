#include <stdio.h>
#include <inttypes.h>
/*
Составить функцию, которая преобразует текущий символ цифры в число. Написать программу считающую сумму цифр в тексте.
int digit_to_num(char c)
 */

int32_t digit_to_num(char c);


int main(void)
{
    char c;
    int32_t sum=0,num;
    while((c=getchar())!='.')
    {
        if((num = digit_to_num(c))>=0)
            sum +=num;
    }
    printf("%"PRId32"\n",sum);
    return 0;
}


int32_t digit_to_num(char c)
{
    if(c >= 0x30 && c <= 0x39)
        return c-0x30;
    return -1;
}
