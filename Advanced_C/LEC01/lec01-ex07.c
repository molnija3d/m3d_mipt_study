#include <stdio.h>
#include <inttypes.h>

int32_t unset_right(int32_t a)
{
        return a & ~0x1;
        //return a & (a - 1);
}

int32_t main(void)
{

        int32_t a, b;
        scanf("%d", &a);
        printf("%x\n", a);
        b = unset_right(a);
        printf("%x\n", b);
        return 0;
}
