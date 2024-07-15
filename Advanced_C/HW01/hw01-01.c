#include <stdio.h>
#include <inttypes.h>

int main(void)
{
        uint32_t n = 0, cnt = 0;
        uint32_t tmp = 0;
        scanf("%" SCNd32, &n);
        
        for(uint32_t i = 0; i < n; i++)
        {
                uint32_t a = 0;
                scanf("%" SCNd32, &a);
                if (a > tmp)
                {
                        tmp = a;
                }
                else if( a == tmp )
                {
                        cnt++;
                }

        }
        
        printf("%" PRIu32 "\n", ++cnt);
        return 0;
}
