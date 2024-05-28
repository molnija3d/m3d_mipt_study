#include <inttypes.h>
#include <stdio.h>
#include "temp_sys.h"

uint8_t menu(params my_args)
{
    switch (my_args.item)
    {
    case FULL:
        printf("FILE: %s\n", my_args.file);
        get_stats(my_args.file, FULL, 0);
        break;

    case MONTH:
        printf("MONTH SPECIFIED %d\n", my_args.month);
        printf("FILE: %s\n", my_args.file);
        get_stats(my_args.file, MONTH, my_args.month);
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
        if (!strcmp(argv[1], "-h"))
        {
            p_args.item = HELP;
        }
        else
        {
            p_args.item = WRONG;
        }
        break;

    case 3:
        if (!strcmp(argv[1], "-f"))
        {
            p_args.item = FULL;
            p_args.file = argv[2];
        }
        else
        {
            p_args.item = WRONG;
        }
        break;

    case 5:
        if (!strcmp(argv[1], "-f") && !strcmp(argv[3], "-m"))
        {
            p_args.item = FULL;
            p_args.file = argv[2];
            p_args.month = atoi(argv[4]);

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