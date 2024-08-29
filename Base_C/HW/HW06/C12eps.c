#include <stdio.h>
#include <inttypes.h>
#include <math.h>
/*
Составить функцию, которая вычисляет синус как сумму ряда (с точностью 0.001)
sin(x) = x - x3/3! + x5/5! - x7/7! + ...(x в радианах)
float sinus(float x)
*/
const float EPS = 0.0001;
const float PI = 3.1415926535; 

float sinus(float x, float eps);

int main(void)
{
    float x;
    scanf("%f",&x);
    x *= PI / 180.;
    printf("%.3f\n",sinus(x,EPS));
    return 0;
}

/*sin(x) = x - x3/3! + x5/5! - x7/7 + ...*/
float sinus(float x, float eps)
{
    float sin=0.f, fact = 1.0f, x_x = x*x, Xn=0;
    float p_x = x;
    int sign=1,i=1;
    do
    {
        fact /= i;
        Xn = sign*p_x*fact;
        sin += Xn;
        fact /= (i+1);
        sign = -sign;
        p_x *= x_x;
        i+=2;
    }
    while(fabs(Xn)>eps);
    
        return sin;
}

