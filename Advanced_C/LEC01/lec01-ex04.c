#include <stdio.h>
#include <inttypes.h>


int32_t invert5(int32_t f)
{
    return f^0x1F;
}

int main(void)
{
    int32_t a, b;
    scanf("%d",&a);
    b = invert5(a);
    printf("%x %x\n", 0x1F, ((1 << 5) - 1));
    printf("%x\n%x\n", a, b);
    return 0;
}
