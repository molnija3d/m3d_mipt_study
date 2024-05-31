#include "temp_api.h"

uint8_t menu(params my_args)
{
    switch (my_args.item)
    {
    case FULL:
        printf("FILE: %s\n", my_args.file);
        get_stats(my_args);
        break;

    case MONTH:
        printf("MONTH SPECIFIED >>> %s <<<\n", num_to_str(my_args.month - 1));
        printf("FILE: %s\n", my_args.file);
        get_stats(my_args);
        break;

    case WRONG:
        printf("WRONG ARGUMENTS!\n");
    case HELP:
    default:
        printf("\'-h\' - to show help\n");
        printf("\'-f filename.csv\' - input file name\n");
        printf("\'-m MM\' - to show stat only for specific month\n");
    }
    return 0;
}
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