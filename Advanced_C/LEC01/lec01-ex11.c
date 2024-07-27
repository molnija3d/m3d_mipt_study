#include <stdio.h>
#include <inttypes.h>

union floatbit
{
    float value;
    struct
    {
        uint32_t mant : 23;
        uint32_t exp : 8;
        uint32_t sign : 1;
    } bit;
};

float mult4(float f)
{
    union floatbit tmp;
    tmp.value = f;
    tmp.bit.exp += 2;
    return tmp.value;
}

int32_t main(void)
{
    float a, b, c;
    scanf("%f", &a);
    printf("%f\n", b = mult4(a));
    printf("%f\n", c = a*4.0);

    return 0;
}
