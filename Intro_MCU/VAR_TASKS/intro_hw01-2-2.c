#include <stdio.h>
#include <inttypes.h>

int main(void) {
    float a = 0;
    printf("Enter float value:");
    scanf("%f", &a);
    int32_t e;
    uint32_t bits = *(uint32_t *)&a;

    e = ((bits >> 23) & 0xff) - 127;
    float m  = (float) (bits & 0x7fffff) / 0x800000 ;
    if(bits >> 31) {
        putchar('-');
    }
    putchar('1');
    putchar(',');

    for(int i = 0; i < 9; i++) {
        m *= 10;
	putchar('0' + m);
	m -= (int) m;
    }
    
    putchar('*');
    putchar('2');
    putchar('^');

    if(e < 0){
	    putchar('-');
	    e = -e;
    }
    
    if(e > 99){
	    putchar('1');
	    e %= 100;
    }
    if(e > 9){
	    putchar('1');
	    e %= 10;
    }
    putchar('0' + e);
    return 0;

}
