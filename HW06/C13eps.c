#include <stdio.h>
#include <inttypes.h>
#include <math.h>
/*
Составить функцию, которая вычисляет синус как сумму ряда (с точностью 0.001)
cos(x) = 1 - x2/2! + x4/4! - x6/6! + ... (x в радианах)
float cosinus(float x)
*/
const float EPS = 0.0001;
const float PI = 3.1415926535; 

float cosinus(float x, float EPS);

int main(void)
{
    float x;
    scanf("%f",&x);
    x *= PI / 180.;
    printf("%.3f\n",cosinus(x,EPS));
    return 0;
}

/*cos(x) = 1 - x2/2! + x4/4! - x6/6! + ...*/
float cosinus(float x, float eps)
{
    float cos=1.f, fact = 1.f, x_x = x*x,Xn=0;
    float p_x = x_x;
    int sign=-1,i=2;

    do
    {
        fact /= i;
        Xn = sign*p_x*fact;
        cos += Xn;
        fact /= (i+1);
        sign = -sign;
        p_x *= x_x;
        i+=2;
    }
    while(fabs(Xn)>eps);
    
    return cos;
}

