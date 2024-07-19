#include <stdio.h>
#include <inttypes.h>


uint32_t extract_bit(uint32_t n, uint8_t k)
{
    return n & ~((1 << (k + 1)) - 1);
}
