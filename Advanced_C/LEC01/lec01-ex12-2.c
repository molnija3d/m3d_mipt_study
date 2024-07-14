#include <stdio.h>
#include <inttypes.h>

uint32_t count_nums(int32_t n)
{
        uint8_t a = 0;
        do
        {
            a += n & 0x1;
        }
        while(n >>= 1);
        return a;
}

int32_t main(void)
{
        int32_t a;
        uint32_t b;
        scanf("%d", &a);
        b = count_nums(a);
        printf("%d\n", b);
        return 0;
}
