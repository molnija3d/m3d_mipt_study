#include <stdio.h>
#include <inttypes.h>

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hr;
    uint8_t min;
    int8_t temp;
} sensor_data;

typedef struct
{
    float average;
    int8_t min;
    int8_t max;
} stat;

enum
{
    HELP,
    FULL,
    MONTH,
    WRONG
};

int8_t get_data_row(FILE *inp, sensor_data *data);
int8_t get_stats(char *fname, int8_t mode, int8_t month);
int8_t stat_calc(stat *s_month, sensor_data row, int8_t month);