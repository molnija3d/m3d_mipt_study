#include <stdio.h>
#include <inttypes.h>


int32_t isEqual(int32_t a, int32_t b)
{
    return !(a^b);
}

int main(void)
{
    int32_t a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", isEqual(a,b));

    return 0;
}
