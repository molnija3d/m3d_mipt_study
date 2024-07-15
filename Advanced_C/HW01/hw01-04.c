#include <stdio.h>
#include <inttypes.h>

uint32_t extract_bit(uint32_t n, uint8_t k)
{
        return n & ((1 << k) - 1);
}

int main()
{
        uint32_t n = 0, ex = 0;
        uint8_t k = 0;
        scanf("%" SCNu32"%" SCNu8, &n, &k);
        ex = extract_bit(n, k);
        printf("%" PRIu32"\n",ex);
        
        return 0;
}
