#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
// function count
#define F_CNT 3

typedef float (* func)(float);

//function prototypes
float f0(float x), f1(float x), f2(float x);

//function to find root between f(x) and g(x) in [a,b] with eps accuracy
float root(func f, func g, float a, float b, float eps);

//plot functions in [a,b]. fn[] - array of functions
int8_t plot_functions(func fn[], float a, float b, int32_t steps);

//find_roots - find roots between f1(x), f2(x), f3(x). fn - array of functions, *roots - array of roots
void find_roots(func fn[], float *roots);

//find_interals - find ingegrals of functions in fn[] array.
//It uses values from *roots array and calculated result in *integrals array
void find_integrals(func fn[], float *roots, float *integrals);

//interal - calculates an integral of function f in [a,b] with eps2 accuracy
float integral(func f, float a, float b, float eps2);

//prints help
void print_help();

int main(int argc, char *argv[]) {
    if(argc > 1 ) {
	    //using standart function getopt to parse arguments
        char *opts = "ahrpf:ts";
        int32_t opt = 0;
	
	//function array
        func fn[F_CNT] = {&f0, &f1, &f2};
        float roots[3], integrals[3];
	
	//num - function number in command options
        int8_t num = -1;

        while((opt = getopt(argc, argv, opts)) != -1) {
            switch(opt) {
		    //perform all operations in automatic mode
            case 'a':
                plot_functions(fn, 0.5, 4.3, 100);
                printf("--------------------------\n");
                find_roots(fn, roots);
                printf("--------------------------\n");
                find_integrals(fn, roots, integrals);
                printf("--------------------------\n");
                printf("Square between f1(x), f2(x) and f3(x) = %f\n", integrals[0] - integrals[1] - integrals[2]);
                break;
		//find roots only
            case 'r':
                find_roots(fn, roots);
                break;

		//plot functions only
            case 'p':
                plot_functions(fn, 0.5, 4.3, 100);
                break;
		
		//select specified function number
            case 'f':
                num = optarg[0] - '0';
                break;
		
		//test specified function
            case 't':
                if(num > -1 && num < 3) {
                    switch(num) {
                    case 0:
                        roots[0] = root(fn[0],fn[2], 0.5, 1, 0.00001);
                        printf("root(f0, f2) = %f\n", roots[0]);
                        break;
                    case 1:
                        roots[1] = root(fn[1],fn[2], 3, 3.5, 0.00001);
                        printf("root(f1, f2) = %f\n", roots[1]);
                        break;
                    case 2:
                        roots[2] = root(fn[0],fn[1], 3.5, 4, 0.00001);
                        printf("root(f0, f1) = %f\n", roots[2]);
                        break;
                    }
                }
                else {
                    printf("Function number should be in 0..%d\n", F_CNT);
                }
                break;

		//calculating square between functions
            case 's':
                printf("--------------------------\n");
                find_roots(fn, roots);
                printf("--------------------------\n");
                find_integrals(fn, roots, integrals);
                printf("--------------------------\n");
                printf("Square between f1(x), f2(x) and f3(x) = %f\n", integrals[0] - integrals[1] - integrals[2]);
                break;

		//printing help
            default:
                print_help();
            }
        }
    }
    else
    {
        print_help();
    }
    return 0;
}

void print_help() {
    printf("Command line options:\n");
    printf("-a :	automatic mode\n");
    printf("-h :	print help\n");
    printf("-r :	find roots\n");
    printf("-s :	find square between f1(x), f2(x) and f3(x)\n");
    printf("-p :	plot graph\n");
    printf("-f [n]:	select function\n");
    printf("-t :	test selected function\n");
}

void find_integrals(func fn[], float *roots, float *integrals) {
    integrals[0] = integral(fn[0], roots[0], roots[2], 0.0001);
    integrals[1] = integral(fn[1], roots[1], roots[2], 0.0001);
    integrals[2] = integral(fn[2], roots[0], roots[1], 0.0001);
    printf("Square f0(x) = %f\nSquare f1(x) = %f\nSquare f2(x) = %f\n", integrals[0], integrals[1], integrals[2]);

}

//find integral with trapezoid method
float integral(func f, float a, float b, float eps2) {
    float sum = 0;
    float h = (b - a) * eps2;
    for(float x = a + h; x < b - h; x += h) {
        sum += 0.5 * h * (f(x) + f(x + h));
    }
    return sum;
}

void find_roots(func fn[], float *roots) {
    roots[0] = root(fn[0],fn[2], 0.5, 1, 0.00001);
    printf("root(f0, f2) = %f\n", roots[0]);

    roots[1] = root(fn[1],fn[2], 3, 3.5, 0.00001);
    printf("root(f1, f2) = %f\n", roots[1]);

    roots[2] = root(fn[0],fn[1], 3.5, 4, 0.00001);
    printf("root(f0, f1) = %f\n", roots[2]);
}

//using gnu_plot to plot functions
int8_t plot_functions(func fn[], float xl, float xr, int32_t step_cnt) {
    int8_t res = 0;
    //testing if gnuplot persistent and opening a pipe
    FILE *gnuplot_p = popen("gnuplot -persistent","w");
    if(gnuplot_p != NULL) {
	    
        //prepairing a graph
        fprintf(gnuplot_p, "set title 'Visualisation of functions. Zelenin-EV' font 'Helvetica Bold, 20'\n");
        fprintf(gnuplot_p, "set xlabel 'x'\n");
        fprintf(gnuplot_p, "set ylabel 'y'\n");
        fprintf(gnuplot_p, "set xrange [0.5:4.5]\n");
        fprintf(gnuplot_p, "set yrange [0:7]\n");
        fprintf(gnuplot_p, "set grid\n");

	//opening a file for function data
        char fname[20] = "_data.txt";
        FILE *f_data = fopen(fname, "w");
        if(f_data != NULL) {
	    //calculating functions data and writing int in a file
            double x = 0, y = 0, step = 0;
            step = fabs(xr - xl)/step_cnt;
            for(int32_t j = 0; j < step_cnt; j++)
            {
                x = xl + j * step;
                fprintf(f_data,"%f ", x);
                for(int8_t i = 0; i < F_CNT; i++)
                {
                    y = fn[i](x);
                    fprintf(f_data,"%f ", y);
                }
                fprintf(f_data,"\n");
            }
            fclose(f_data);

	    //prepairing a plot command
            fprintf(gnuplot_p, "plot ");
            for(int8_t i = 0; i < F_CNT; i++)
            {
                fprintf(gnuplot_p, "'_data.txt' using 1:%d with lines title 'f%d(x)', ", i + 2, i);
            }

	    //perform a plot
            fprintf(gnuplot_p, "\n");
        }
	//closing gnu_plot pipe
        fflush(gnuplot_p);
        pclose(gnuplot_p);
    }
    else {
        res = 1;
    }
    return res;
}

//functions specified
float f0(float x) {
    return 0.6 * x + 3;
}

float f1(float x) {
    return (x - 2) * (x - 2) * (x - 2) - 1;
}

float f2(float x) {
    return 3 / x;
}

//finding a root of two functions f(x) and g(x) in [a,b]
//using a chorde method
float root(func f, func g, float a, float b, float eps) {
    size_t stepcount=0;
    while(fabs(b - a) > eps) {
        float fa = f(a), fb = f(b), ga = g(a), gb = g(b);
        a = b - (b - a) * (fb - gb) / (fb - gb + ga - fa);
        b = a - (a - b) * (fa - ga) / (fa - ga + gb - fb);
        stepcount++;
    }
    printf("%ld steps for ",stepcount);
    return b;
}

