#include <stdio.h>
#include <inttypes.h>

struct pack_array
{
    uint32_t array;
    uint32_t count0:8;
    uint32_t count1:8;
};

void array2struct(int arr[], struct pack_array * pack)
{
    pack->array = 0;
    pack->count0 = 0;
    pack->count1 = 0;
    for(uint8_t i = 0; i < 32; i++)
    {
        pack->array <<= 1;
        pack->array |= arr[i] & 0x1;
        if (arr[i] == 0)
        {
            pack->count0++;
        }
        else
        {
            pack->count1++;
        }
    }
}

int main()
{
    struct pack_array pack;
    int arr[32] = {0,0,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,1,0,0,0};
    array2struct(arr,&pack);
    printf("%d %d\n", pack.count0, pack.count1);

    return 0;
}
