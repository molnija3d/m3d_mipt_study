#include <stdio.h>
#include <inttypes.h>
/*
Дана последовательность целых чисел через пробел, завершающаяся числом 0.
Выведите все нечетные числа из этой последовательности, сохраняя их порядок. Составить рекурсивную функцию.
*/
void r_spare(void);

int main(void)
{
    r_spare();
    return 0;
}

void r_spare(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    if(n != 0)
    {
     if(n%2)
       printf("%"PRId32" ",n);
     r_spare();
    }

}
