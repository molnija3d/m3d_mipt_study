#include <stdio.h>
#include <inttypes.h>

_Bool is_p_4(int32_t n)
{
        return n != 0 && !(n & (n-1)) && (n & 0x55555555); 
}

int32_t main(void)
{

        int32_t a, b, c;
        for(int i = 0; i < 4097; i++)
        {
           if (b = is_p_4(i))
           {
             printf("%d %d %d\n", i, b, i & (i - 1));
           }
        }
        return 0;
}
