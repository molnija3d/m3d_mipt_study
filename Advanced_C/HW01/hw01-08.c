#include <stdio.h>
#include <inttypes.h>


int main()
{
    uint32_t n = 0;
    int32_t a = 0, res = 0;
    scanf("%" SCNu32, &n);
    scanf("%" SCNd32, &res);

    while(--n)
    {
        scanf("%" SCNd32, &a);
        res ^= a;
    }
    printf("%" PRId32 "\n", res);
    return 0;
}
