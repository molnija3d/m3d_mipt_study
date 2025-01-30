#include <inttypes.h>
#include <stdio.h>
typedef union {
	uint32_t u32;
	uint16_t u16[2];
	uint8_t byte[4];
	float f;
} my_type;

int main (void){
	my_type val;
	val.f = 12344.3453;
	printf("u32 = %u\n", val.u32);
	printf("u16_0 = %u u16_1 = %u\n", val.u16[0], val.u16[1]);
	printf("byte = %u byte = %u byte = %u byte = %u\n", val.byte[0], val.byte[1], val.byte[2], val.byte[3]);
	printf("float = %f\n", val.f);

	return 0;
}
