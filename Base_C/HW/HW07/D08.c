#include <stdio.h>
#include <inttypes.h>
/*
Составить рекурсивную функцию, Выведите все числа от A до B включительно, в порядке возрастания, если A < B, или в порядке убывания в противном случае.
*/
void r_printab(int32_t a,int32_t b);

int main(void)
{
    int32_t a,b;
    scanf("%"PRId32"%"PRId32,&a,&b);
    r_printab(a,b);
    return 0; 
}

void r_printab(int32_t a,int32_t b)
{
    if(a < b)
      {
        printf("%"PRId32" ",a);
        r_printab(++a,b);  
      }
    else if (a>b)
      {
        printf("%"PRId32" ",a);
        r_printab(--a,b);  
      }
    else 
        printf("%"PRId32" ",a);
}
