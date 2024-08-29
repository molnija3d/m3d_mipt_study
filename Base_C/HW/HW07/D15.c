#include <stdio.h>
#include <inttypes.h>
/*
Дана последовательность ненулевых целых чисел, завершающаяся числом 0. Ноль в последовательность не входит.
Определите наибольшее значение числа в этой последовательности. Для решения задачи необходимо написать рекурсивную функцию вида:
int max_find(int max)
*/
int max_find(int max);

int main(void)
{
    printf("%d",max_find(0));
    return 0;
}

int max_find(int max)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    if(n != 0)
        max = max_find(n);
    else 
       n = max;
    return (n > max) ? n : max;
}
