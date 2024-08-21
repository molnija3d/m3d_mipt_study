#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef float(*function)(float);

//(-2, -1.5) (-1.5, -1) (-1, -0.5) (-0.5, 0)
float f(float x) {
    //return 8*x*x + 1;
    return 8*x*x*x*x + 32*x*x*x + 40*x*x + 16*x + 1;
}

float testf(float x) {
    return 2;
}

float calcIntegralSquare(float xl, float xr, size_t n, function f) {
    float sum = 0;
    float h = (xr-xl)/n;
    for(size_t i=0; i<n; i++) {
        sum += f(xl);
        xl  += h;
    }
    return sum*h;
}

float calcIntegralTrap(float xl, float xr, size_t n, function f) {
    float sum = 0;
    float h = (xr-xl)/n;
    for(float x=xl+h; x<xr-h; x+=h) {
        sum += 0.5*h*(f(x)+f(x+h));
    }
    return sum;
}

float calcIntegralSimpson(float xl, float xr, size_t n, function f) {
    float sum = 0;
    float h = (xr-xl)/n;
    for(float x=xl+h; x<xr-h; x+=h) {
        sum += h/6.0*(f(x) + 4.0*f(0.5*(x+x+h)) + f(x+h));
    }
    return sum;
}

float calcIntegralMonteCarlo2(float xl, float xr, float fmax, size_t n, function f) {
    size_t in_d = 0;
    float width = fabs(xr-xl), height = fmax;
    int sign = 0;
    sign = xl > 0 ? 1 : -1;
    for(size_t i=0; i<n; i++) {
        float x = ((float)rand()/(float)RAND_MAX) * width + sign*fabs(xl);
        float y =  (float)rand()/(float)RAND_MAX  * height;
        if(y<f(x))
            in_d++;
    }
    return fabs( (float)in_d / n * width * height  );
}

float calcIntegralMonteCarlo(float xl, float xr, float fmax, size_t n, function f) {
    size_t in_d = 0;
    float width = fabs(xr-xl), height = fmax;
    for(size_t i=0; i<n; i++) {
        float x = ((float)rand()/(float)RAND_MAX) * width - fabs(xl);
        float y =  (float)rand()/(float)RAND_MAX  * height;
        if(y<f(x))
            in_d++;
    }
    return fabs( (float)in_d / n * width * height  );
}

int main()
{
    printf("calcIntegralSquare integral %f\n", calcIntegralSquare(0,2,1000,testf));
    printf("calcIntegralSquare = %f\n", calcIntegralSquare(-1.382683,-0.617316,1000,f));
    printf("calcIntegralTrap = %f\n", calcIntegralTrap(-1.382683,-0.617316,1000,f));
    printf("calcIntegralSimpson = %f\n", calcIntegralSimpson(-1.382683,-0.617316,1000,f));
    printf("calcIntegralMonteCarlo = %f\n", calcIntegralMonteCarlo(-1.382683,-0.617316,1,100000,f));
    printf("calcIntegralMonteCarlo2 = %f\n", calcIntegralMonteCarlo2(-1.382683,-0.617316,1,100000,f));
    return 0;
}




