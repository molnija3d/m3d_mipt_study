#include <stdio.h>
#include <inttypes.h>
/*
Написать рекурсивную функцию и используя ее решить задачу.
Напечатать цифры введенного натурального числа в порядке следования(слева направо) через пробел.
void print_digits(int n)
*/
void print_digits(int n);

int main(void)
{
    int n;
    scanf("%d",&n);
    print_digits(n);
    return 0;
}

void print_digits(int n)
{
    if(n>0)
    {   
        print_digits(n/10);        
        printf("%d ", n%10);

    }
}
