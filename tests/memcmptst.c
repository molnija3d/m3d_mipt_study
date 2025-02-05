#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>



int main(void){
	uint16_t my_test[13] = {0x4455, 0x3322, 0x1234, 0xabcd};
	uint32_t cmp3 = 0x33224455U; 
	uint64_t cmp2 = 0xabcd123433224455; 
	int32_t res = 0;
	res = memcmp(my_test, &cmp3, 4);
	res = memcmp(my_test, &cmp2, 8);
	res = memcmp(my_test, &(uint64_t){0xabcd123433224455}, 8);

	
	return 0;
}
