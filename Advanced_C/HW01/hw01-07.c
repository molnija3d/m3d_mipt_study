#include <stdio.h>
#include <inttypes.h>

uint32_t reverse_two_top(uint32_t n)
{
        return n ^ (0xFF << 24); 
}

int main()
{
        uint32_t n = 0, res = 0;
        scanf("%" SCNu32, &n);
        res = reverse_two_top(n);
        printf("%" PRIu32"\n", res);
        
        return 0;
}
