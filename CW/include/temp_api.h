#ifndef _TEMP_API_H
#define _TEMP_API_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "temp_sys.h"
enum
{
    H_MONTH,
    H_YEAR
};

typedef struct list
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hr;
    uint8_t min;
    int8_t temp;
    struct list *next;
    struct list *prev;
} sensor_data;

typedef struct
{
    float average;
    int8_t min;
    int8_t max;
    _Bool stored;
} stat;

int8_t add_data(FILE *inp, sensor_data **data);
int8_t parse_row(FILE *inp, sensor_data **data);
void parse_row_args(int8_t *err, int8_t argcnt, int16_t num, sensor_data **data);
int8_t free_rows(sensor_data **list);
int8_t del_row(sensor_data **data);
int8_t get_stats(params my_param);
int8_t stat_print_list(sensor_data **rows, uint8_t month);
const char *num_to_str(uint8_t month);
int8_t print_month(stat *m_stat, int8_t cur_month);
void print_header(uint8_t hdr);
void print_year_err(sensor_data **rows);
void print_year_data(sensor_data **rows, int8_t yr_t_max, int8_t yr_t_min, float avg);

#endif