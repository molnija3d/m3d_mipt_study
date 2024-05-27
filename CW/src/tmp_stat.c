#include "temp_api.h"
#include <strings.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    uint8_t menu_item = 0;
    char *file = NULL;
    int month = 0;

    // parse arguments
    switch (argc)
    {
    case 2:
        if (!strcmp(argv[1], "-h"))
        {
            menu_item = HELP;
        }
        else
        {
            menu_item = WRONG;
        }
        break;

    case 3:
        if (!strcmp(argv[1], "-f"))
        {
            menu_item = FULL;
            file = argv[2];
        }
        else
        {
            menu_item = WRONG;
        }
        break;

    case 5:
        if (!strcmp(argv[1], "-f") && !strcmp(argv[3], "-m"))
        {
            menu_item = FULL;
            file = argv[2];
            month = atoi(argv[4]);

            if (month > 0 && month < 13)
            {
                menu_item = MONTH;
            }
            else
            {
                menu_item = WRONG;
            }
        }
        else 
        {
            menu_item = WRONG;
        }
        break;
        
    default:
        menu_item = WRONG;
        break;
    }

    //
    switch (menu_item)
    {
    case FULL:
        printf("FILE: %s\n", file);
        get_stats(file, FULL, 0);
        break;

    case MONTH:  
        printf("MONTH SPECIFIED %d\n", month);
        printf("FILE: %s\n", file);
        get_stats(file, MONTH, month);
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