#include <stdio.h>
void print_simple(int n);
int main(void)
{
    int n;
    scanf("%d",&n);
    print_simple(n);
    return 0;
}

void print_simple(int n)
{
    int div=2;
    while (n!=1)
    {
        if(n%div==0)
        {
            n/=div;
        }
        else
            div+=1;
    }
}
