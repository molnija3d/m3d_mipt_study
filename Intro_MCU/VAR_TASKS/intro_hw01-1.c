#include <inttypes.h>
#include <stdio.h>
#define BITSET(data) (data = (uint32_t) - 1)
#define BITRESET(data, bits) (data &= ~(bits))

void bitreset(uint32_t *data, uint32_t bit);
void bitset(uint32_t *data);

int main(void) {
    uint32_t data;
    printf("data = %x\n", data);
    bitset(&data);
    printf("data = %x\n", data);
    bitreset(&data, 0b11 << 3);
    printf("data = %x\n", data);
    BITSET(data);
    printf("data = %x\n", data);
    BITRESET(data, 0b11 << 4);
    printf("data = %x\n", data);
    return 0;
}

void bitreset(uint32_t *data, uint32_t bit) {
    *data &= ~bit;
}

void bitset(uint32_t *data) {
    *data = (uint32_t) -1;
}
