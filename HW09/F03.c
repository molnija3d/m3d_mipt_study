/*
Цифры по возрастанию
Написать функцию и программу демонстрирующую работу данной функции.
Вывести в порядке возрастания цифры, входящие в десятичную запись натурального числа N, не более 1000 цифр.
Цифра пробел сколько раз данная цифра встречается в числе.
Input format
Натуральное число не более 1000 цифр
Output format
Цифры входящие в число через пробел в порядке возрастания. От самой младшей цифры до самой старшей и количество.
*/
#include <stdio.h>
#include <inttypes.h>

void inparr(int32_t *arr);
void printNumCount(int32_t* arr);

int main(void)
{
    int32_t nums[1001]={-1};
    inparr(nums);
    printNumCount(nums);

    return 0;
}

void inparr(int32_t* arr)
{
    char c;
    int i=0;

    while((c=getchar())!='\n')
        arr[i++]=c-0x30;

    arr[i]=-1;
}
void printNumCount(int32_t* arr)
{
    uint32_t buff[10]= {0};
    for(int i = 0; arr[i]>-1; i++)
        ++buff[arr[i]];

    for(int i=0; i < 10; i++)
        if(buff[i])
            printf( "\n%" PRId32 " %" PRId32 "\n",i,buff[i]);
}
