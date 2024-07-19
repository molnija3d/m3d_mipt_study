#include <stdio.h>
#include <inttypes.h>

uint32_t reverse_bits(uint32_t n)
{
    uint32_t a = 0;
    while(n)
    {
        a <<= 1;
        a |= n & 0x1;
        n >>= 1;
    }
    return a;
}

uint32_t reverse_bits_2(uint32_t n)
{
    uint32_t NO_OF_BITS = sizeof(n) * 8;
    uint32_t reverse_num = 0;
    int32_t i;
    for (i = 0; i < NO_OF_BITS; i++)
    {
        if((n & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);

    }
    return reverse_num;
}

int32_t main(void)
{
    uint32_t a;
    uint32_t b;
    scanf("%" SCNu32, &a);
    b = reverse_bits(a);
    printf("%" PRIu32 "\n", b);
    b = reverse_bits_2(a);
    printf("%" PRIu32 "\n", b);
    return 0;
}
