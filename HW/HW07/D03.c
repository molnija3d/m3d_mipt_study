#include <stdio.h>
#include <inttypes.h>
/*
Дано целое не отрицательное число N. Выведите все его цифры по одной, в обратном порядке, разделяя их пробелами или новыми строками. 
Составить рекурсивную функцию.
*/
void r_reverse(int32_t n);
int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    r_reverse(n);
    return 0; 
}

void r_reverse(int32_t n)
{
    static int32_t prev = 0;
    if(n > 0)
      {
        prev = n;
        printf("%"PRId32" ",n%10);  
        r_reverse(n/10);
      }
    else if (prev == 0 && n == 0)
        printf("0 ");
}
