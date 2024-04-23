#include <stdio.h>
#include <inttypes.h>

float cosinus(float x);

int main(void)
{
    float x;
    scanf("%f",&x);
    x *= 3.141592 / 180.;
    printf("%.3f\n",cosinus(x));
    return 0;
}

/*cos(x) = 1 - x2/2! + x4/4! - x6/6! + ...*/
float cosinus(float x)
{
    float cos=1.f, fact = 1.f, x_x = x*x;
    float p_x = x_x;
    int sign=-1;
    for(int32_t i=2;i<8;i+=2)
    {
     fact /= i;
     cos += sign*p_x*fact;
     fact /= (i+1);
     sign = -sign; 
     p_x *= x_x;
    }
    return cos;
}
    
