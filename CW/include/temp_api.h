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

int8_t get_row(FILE *inp, sensor_data *data);
int8_t get_stats(char *fname, int8_t mode, int8_t month);
int8_t stat_print(sensor_data *rows, uint32_t r_cnt, uint8_t month);
int32_t rows_count(FILE *fl);