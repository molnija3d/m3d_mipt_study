#include <stdio.h>
#include <inttypes.h>

uint32_t rrt(uint32_t n, uint32_t rot)
{
        return (n >> rot) | (n << (32 - rot)); 
}

int32_t main(void)
{

        uint32_t a, b, n;
        scanf("%d %d", &a, &n);
        b = rrt(a, n);
        printf("%x %x\n", a, b);
        return 0;
}
