#include <stdio.h>
#include <inttypes.h>

int32_t extract_exp(float f)
{
    union
    {
        float f;
        struct
        {
            uint32_t m:23;
            uint32_t exp:8;
            uint32_t s:1;
        } field;
    } fl;
    fl.f = f;
    return fl.field.exp;

}

int32_t main(void)
{
    float f;
    uint32_t exp;
    scanf("%f", &f);
    exp = extract_exp(f);
    printf("%" PRIu32 "\n", exp);
    return 0;
}
