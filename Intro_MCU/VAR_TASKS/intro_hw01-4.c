#include <inttypes.h>
#include <stdio.h>
void set_value(uint32_t val, uint64_t addr);
int main(void){ 
  uint64_t addr = 0x7fffffffe384;
  printf("%p\n", &addr);
  set_value(1234, addr);
  printf("Val at addr %lu  = %u\n", addr, *(uint32_t*) addr);
  
return 0;
}
void set_value(uint32_t val, uint64_t addr){
    uint32_t *p = (uint32_t *) addr;
    *p = val;
}
