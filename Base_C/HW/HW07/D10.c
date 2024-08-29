#include <stdio.h>
/*
Дано натуральное число n ≥ 1. Проверьте, является ли оно простым. Программа должна вывести слово YES, если число простое или NO в противном случае. Необходимо составить рекурсивную функцию и использовать ее.
int is_prime(int n, int delitel)
*/
int is_prime(int n, int delitel);

int main(void)
{
    int n;
    scanf("%d",&n);
    is_prime(n,2)? printf("YES\n"): printf("NO\n");
    return 0;
}

int is_prime(int n, int delitel)
{
    int res = n%delitel;
    if(n == 2 || n == 3)
        return 1;
    else if (n == 1)
        return 0;
    if (delitel * delitel <= n && res)
        res = is_prime(n,++delitel);

    return res;
}
