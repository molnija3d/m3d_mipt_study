#include <stdio.h>
#include <inttypes.h>

int extractExp(float f)
{
    union
    {
        float val;
        struct
        {
            uint32_t m: 23;
            uint32_t exp: 8;
            uint32_t s: 1;
        } bit;
    } in;
    in.val = f;
    return in.bit.exp;
}

int main()
{
    float f;
    scanf("%f", &f);
    printf("%d\n", extractExp(f));
    return 0;
}
