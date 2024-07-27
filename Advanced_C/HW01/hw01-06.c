#include <stdio.h>
#include <inttypes.h>

uint8_t count_ones(uint32_t n)
{
    uint8_t cnt = 0;
    while (n)
    {
        cnt++;
        n &= n - 1;
    }
    return cnt;
}

int main()
{
    uint32_t n = 0;
    scanf("%" SCNu32, &n);
    printf("%" PRIu8"\n", count_ones(n));

    return 0;
}
