#include <stdio.h>
#include <inttypes.h>
/*
Дано натуральное число N. Выведите все его цифры по одной, в прямом порядке, разделяя их пробелами или новыми строками. Необходимо реализовать рекурсивную функцию.
void print_num(int num)
*/
void print_num(int num);

int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    (n > 0)? print_num(n) : printf("0 ");
    return 0; 
}

void print_num(int num)
{
    if(num)
      {
        print_num(num/10);  
        printf("%"PRId32" ",num%10);  
      }
}
