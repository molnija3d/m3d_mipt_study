#ifndef _TEMP_SYS_H
#define _TEMP_SYS_H

#include <inttypes.h>

typedef struct 
{
    uint8_t item;
    char *file;
    uint8_t month;
} params; 

enum
{
    HELP,
    FULL,
    MONTH,
    WRONG
};

params parse_args(int argc, char *argv[]);
uint8_t menu(params);
char my_strcmp(const char *a, const char *b);
int8_t my_atoi(const char *str);

#endif