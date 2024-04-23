#include <stdio.h>
#include <inttypes.h>

float sinus(float x);

int main(void)
{
    float x;
    scanf("%f",&x);
    x *= 3.141592 / 180.;
    printf("%.3f",sinus(x));
    return 0;
}

/*sin(x) = x - x3/3! + x5/5! - x7/7 + ...*/
float sinus(float x)
{
    float sin=0.f;
    float x_x = x*x;
    float p_x = x;
    float fact = 1.0f;
    int sign=1;
    for(int32_t i=1;i<8;i+=2)
    {
     fact /= i;
     sin += sign*p_x*fact;
     fact /= (i+1);
     sign = -sign;
     p_x *= x_x;
    }
    return sin;
}
    
