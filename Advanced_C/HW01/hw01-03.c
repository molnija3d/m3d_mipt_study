#include <stdio.h>
#include <inttypes.h>


uint32_t rsht(uint32_t n, uint32_t rot)
{
    return ( n >> rot ) | ( n << (32 - rot));
}

int main(void)
{
    uint32_t n, rot;
    scanf("%" SCNu32"%" SCNu32, &n, &rot);
    printf("%" PRIu32"\n", rsht(n, rot));
    return 0;
}


