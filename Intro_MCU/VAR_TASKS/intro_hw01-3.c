#include <inttypes.h>
uint32_t arr[5];
int setbit(int index, int bit, uint32_t array[]);
int clearbit(int index, uint32_t array[]);
int getbit(int index, uint32_t array[]);

int main(void) {
    setbit(9,1,arr);
    int a = getbit(9, arr);
    setbit(67,1,arr);
    a = getbit(67, arr);
    clearbit(67,arr);
    a = getbit(67, arr);

    return 0;
}

int setbit(int index, int bit, uint32_t array[]) {
    if(bit) {
        array[index >> 5] |= 1 << (0x1F & index);
    } else {
        array[index >> 5] &= ~(1 << (0x1F & index));
    }
    return 0;
}

int clearbit(int index, uint32_t array[]) {
    array[index >> 5] &= ~(1 << (0x1F & index));
    return 0;
}

int getbit(int index, uint32_t array[]) {

    return 1 & array[index >> 5] >> (0x1F & index);
}
