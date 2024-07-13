#include <stdio.h>
#include <inttypes.h>

int32_t sub1_if_even(int32_t a)
{
        return a - !(a & 0x1);
}

int32_t main(void)
{

        int32_t a;
        scanf("%d", &a);
        printf("%d\n", sub1_if_even(a));
        return 0;
}
