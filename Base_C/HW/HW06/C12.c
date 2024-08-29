#include <stdio.h>
#include <inttypes.h>
/*
Составить функцию, которая вычисляет синус как сумму ряда (с точностью 0.001)
sin(x) = x - x3/3! + x5/5! - x7/7! + ...(x в радианах)
float sinus(float x)
*/

float sinus(float x);

int main(void)
{
    float x;
    scanf("%f",&x);
    x *= 3.141592 / 180.;
    printf("%.3f\n",sinus(x));
    return 0;
}

/*sin(x) = x - x3/3! + x5/5! - x7/7 + ...*/
float sinus(float x)
{
    float sin=0.f, fact = 1.0f, x_x = x*x;
    float p_x = x;
    int sign=1;
    for(int32_t i=1; i<8; i+=2)
    {
        fact /= i;
        sin += sign*p_x*fact;
        fact /= (i+1);
        sign = -sign;
        p_x *= x_x;
    }
    return sin;
}

