#include <stdio.h>
#include <inttypes.h>
/*
Написать логическую рекурсивную функцию и используя ее определить является ли введенное натуральное число точной степенью двойки.
int is2pow(int n)
*/
int is2pow(int n);

int main(void)
{
    int n;
    scanf("%d",&n);
    printf("%s",is2pow(n) ? "YES\n" : "NO\n");
    return 0;
}

int is2pow(int n)
{
    if (n == 1)
        return 1;
    else if(n == 0)
        return 1;
    else if(!(n%2))
        return is2pow(n/2);
    return 0;
}
