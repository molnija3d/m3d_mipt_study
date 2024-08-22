#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Структура для хранения функции и её производной
typedef double (*Function)(double);

// Определение функций
double f1(double x)
{
    return 0.6 * x + 3;
}

double f2(double x)
{
    return pow((x - 2), 3) - 1;
}

double f3(double x)
{
    return 3 / x;
}

// Производные функций
double f1_derivative(double x)
{
    return 0.6;
}

double f2_derivative(double x)
{
    return 3 * pow((x - 2), 2);
}

double f3_derivative(double x)
{
    return -3 / (x * x);
}

// Функция для нахождения корня уравнения f(x) = g(x)
double root(Function f, Function g, Function f_deriv, Function g_deriv, double a, double b, double eps1, int *iterations)
{
    double x = (a + b) / 2;
    double delta;
    *iterations = 0;

    do
    {
        double f_val = f(x) - g(x);
        double f_deriv_val = f_deriv(x) - g_deriv(x);

        if (fabs(f_deriv_val) < eps1)
        {
            break;
        }

        delta = f_val / f_deriv_val;
        x -= delta;
        (*iterations)++;
    } while (fabs(delta) > eps1);

    return x;
}

// Функция для вычисления определенного интеграла
double integral(Function f, double a, double b, double eps2)
{
    int n = 1;
    double h = (b - a) / n;
    double integral_old = 0;
    double integral_new = (f(a) + f(b)) * h / 2;

    while (fabs(integral_new - integral_old) > eps2)
    {
        integral_old = integral_new;
        n *= 2;
        h = (b - a) / n;
        integral_new = 0;
        for (int i = 0; i < n; i++)
        {
            integral_new += (f(a + i * h) + f(a + (i + 1) * h)) * h / 2;
        }
    }

    return integral_new;
}

// Функция для вывода справки по использованию программы
void print_help()
{
    printf("Usage: program [OPTIONS]\n");
    printf("Options:\n");
    printf("  --help            Show this help message\n");
    printf("  --roots           Find and print roots\n");
    printf("  --iterations      Print number of iterations for finding roots\n");
    printf("  --test            Run tests for root and integral functions\n");
    printf("  --plot            Plot the functions\n");
    printf("\n");
}

// Парсер командной строки
void parse_args(int argc, char *argv[], int *print_roots, int *print_iterations, int *run_tests, int *plot_graphs)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            print_help();
            exit(0);
        }
        else if (strcmp(argv[i], "--roots") == 0)
        {
            *print_roots = 1;
        }
        else if (strcmp(argv[i], "--iterations") == 0)
        {
            *print_iterations = 1;
        }
        else if (strcmp(argv[i], "--test") == 0)
        {
            *run_tests = 1;
        }
        else if (strcmp(argv[i], "--plot") == 0)
        {
            *plot_graphs = 1;
        }
    }

    // Если никаких опций не передано, показать справку
    if (argc == 1)
    {
        print_help();
        exit(0);
    }
}

// Основная программа
int main(int argc, char *argv[])
{
    int print_roots = 0, print_iterations = 0, run_tests = 0, plot_graphs = 0;

    parse_args(argc, argv, &print_roots, &print_iterations, &run_tests, &plot_graphs);

    if (run_tests)
    {
        // Тестирование функций root и integral
        printf("Testing root and integral functions...\n");
        int iterations;
        double root_test = root(f1, f2, f1_derivative, f2_derivative, 0, 4, 1e-6, &iterations);
        double integral_test = integral(f1, 0, 4, 1e-6);

        printf("Test root result: %lf\n", root_test);
        printf("Test integral result: %lf\n", integral_test);
        printf("Root iterations: %d\n", iterations);
    }

    int iterations1, iterations2, iterations3;
    double root1 = root(f1, f2, f1_derivative, f2_derivative, 0, 4, 1e-6, &iterations1);
    double root2 = root(f1, f3, f1_derivative, f3_derivative, 0.1, 4, 1e-6, &iterations2);
    double root3 = root(f2, f3, f2_derivative, f3_derivative, 0.1, 4, 1e-6, &iterations3);

    if (print_roots)
    {
        printf("Roots found:\n");
        printf("Root 1 (f1 = f2): %lf\n", root1);
        printf("Root 2 (f1 = f3): %lf\n", root2);
        printf("Root 3 (f2 = f3): %lf\n", root3);
    }

    if (print_iterations)
    {
        printf("Iterations required:\n");
        printf("Root 1: %d iterations\n", iterations1);
        printf("Root 2: %d iterations\n", iterations2);
        printf("Root 3: %d iterations\n", iterations3);
    }

    if (plot_graphs)
    {
        // Вызов Gnuplot для построения графиков
        FILE *gnuplotPipe = _popen("gnuplot -persistent", "w");

        if (gnuplotPipe)
        {
            fprintf(gnuplotPipe, "set title 'Functions Plot'\n");
            fprintf(gnuplotPipe, "set xrange [0:5]\n");  // Ограничение диапазона X
            fprintf(gnuplotPipe, "set yrange [-1:6]\n"); // Ограничение диапазона Y
            fprintf(gnuplotPipe, "plot 0.6*x + 3 title 'f1 = 0.6x + 3', (x - 2)**3 - 1 title 'f2 = (x - 2)^3 - 1', 3/x title 'f3 = 3/x'\n");
            fflush(gnuplotPipe);
            _pclose(gnuplotPipe);
        }
        else
        {
            printf("Gnuplot not found!\n");
        }
    }

    return 0;
}