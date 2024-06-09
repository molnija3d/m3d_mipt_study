#include "temp_api.h"

uint8_t menu(params my_args)
{
    switch (my_args.item)
    {
    case FULL:
        menu_full(my_args);
        break;

    case MONTH:
        menu_month(my_args);
        break;

    case WRONG:
        menu_wrong(my_args);
    case HELP:
    default:
        menu_help();
    }
    return 0;
}
///parce arguments functions
params parse_args(int argc, char *argv[])
{
    params p_args;

    // parse arguments
    switch (argc)
    {
    case 2:
        if (!my_strcmp(argv[1], "-h"))
        {
            p_args.item = HELP;
        }
        else
        {
            p_args.item = WRONG;
        }
        break;

    case 3:
        if (!my_strcmp(argv[1], "-f"))
        {
            p_args.item = FULL;
            p_args.file = argv[2];
            p_args.month = 0;
        }
        else
        {
            p_args.item = WRONG;
        }
        break;

    case 5:
        if (!my_strcmp(argv[1], "-f") && !my_strcmp(argv[3], "-m"))
        {
            p_args.item = FULL;
            p_args.file = argv[2];
            p_args.month = my_atoi(argv[4]);

            if (p_args.month > 0 && p_args.month < 13)
            {
                p_args.item = MONTH;
            }
            else
            {
                p_args.item = WRONG;
            }
        }
        else
        {
            p_args.item = WRONG;
        }
        break;

    default:
        p_args.item = WRONG;
        break;
    }
    return p_args;
}
/// string functions
char my_strcmp(const char *a, const char *b)
{
    while (*a && *b && *a == *b)
    {
        a++;
        b++;
    }
    return *a - *b;
}

int8_t my_atoi(const char *str)
{
    int8_t res = 0;
    int i = 0;
    if (*str)
    {
        do
        {
            res *= 10;
            res += str[i++] - '0';
        } while (str[i] != '\0');
    }
    return res;
}
/// Menu functions 
void menu_full(params my_args)
{
    printf("FILE: %s\n", my_args.file);
    get_stats(my_args);
}
void menu_month(params my_args)
{
    printf("FILE: %s\n", my_args.file);
    get_stats(my_args);
}
void menu_wrong(params my_args)
{
    printf("WRONG ARGUMENTS!\n");
}
void menu_help(void)
{
    printf("[ -h ] show help\n");
    printf("[ -f filename.csv ] input file name\n");
    printf("[ -m MM ] show stat for specific month only\n");
}

