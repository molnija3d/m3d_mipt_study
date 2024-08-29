#include <stdio.h>
#include <inttypes.h>

int main(void)
{
    float b = 4;
    printf("%f\n", b);
    b *= -1.0f;
    printf("%f\n", b);
    *((uint32_t *)&b) ^= 0x80000000;
    printf("%f\n", b);
}