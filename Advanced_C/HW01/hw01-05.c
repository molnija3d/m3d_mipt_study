#include <stdio.h>
#include <inttypes.h>

uint32_t find_bit(uint32_t n, uint8_t k)
{
    uint32_t mx = 0, tmp = 0;
    do
    {
        tmp = n & ((1 << k) - 1);
        if(mx < tmp)
        {
            mx = tmp;
        }
    }
    while(n >>= 1);
    return mx;
}

int main()
{
    uint32_t n = 0, ex = 0;
    uint8_t k = 0;
    scanf("%" SCNu32"%" SCNu8, &n, &k);
    ex = find_bit(n, k);
    printf("%" PRIu32"\n",ex);

    return 0;
}
