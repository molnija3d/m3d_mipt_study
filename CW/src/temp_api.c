#include "temp_api.h"
#include <stdlib.h>

int8_t get_row(FILE *inp, sensor_data *data)
{
    char c;
    int16_t num = 0;
    int8_t argcnt = 0;
    int8_t err = 0;
    int8_t sign = 1;

    do
    {
        c = fgetc(inp);

        if (c >= '0' && c <= '9')
        {
            num *= 10;
            num += c - '0';
        }
        else if (c == '-')
        {
            if (num == 0)
            {
                sign = -1;
            }
            else
            {
                printf("Wrong '-' symbol in ARG N%d\n", argcnt);
                err = 1;
            }
        }
        else if (c == ';' || c == '\n' || c == EOF)
        {
            switch (argcnt++)
            {
            case 0:
                if (num >= 1900 && num <= 3000)
                {
                    data->year = num;
                }
                else
                {
                    if( c == EOF)
                    {
                      err = -1;  
                    }
                    else
                    {
                        data->year = 0;
                    printf("Wrong YEAR %d\n", num);
                    err = 1;
                    }
                }
                break;
            case 1:
                if (num > 0 && num < 13)
                {
                    data->month = num;
                }
                else
                {
                    data->month = 0;
                    printf("Wrong MONTH %d\n", num);
                    err = 2;
                }
                break;
            case 2:
                if (num > 0 && num < 32)
                {
                    data->day = num;
                }
                else
                {
                    data->day = 0;
                    printf("Wrong DAY %d\n", num);
                    err = 3;
                }
                break;
            case 3:
                if (num >= 0 && num < 25)
                {
                    data->hr = num;
                }
                else
                {
                    data->hr = 0;
                    printf("Wrong HOURS %d\n", num);
                    err = 4;
                }
                break;
            case 4:
                if (num >= 00 && num < 61)
                {
                    data->min = num;
                }
                else
                {
                    data->min = 0;
                    printf("Wrong MINUTES %d\n", num);
                    err = 5;
                }
                break;
            case 5:
                if (num > -100 && num < 100)
                {
                    data->temp = sign * num;
                }
                else
                {
                    data->temp = -127;
                    printf("Wrong TEMP %d\n", num);
                    err = 7;
                }
                break;
            default:
                err = 8;
            }

            if (c == EOF)
            {
                if (argcnt == 6 || argcnt == 1)
                {
                    err = -1;
                }
                else
                {
                    err = -2;
                }
            }
            num = 0;
        }
        else if (c == ' ')
        {
        }
        else
        {
            err = 9;
        }

    } while (c != '\n' && err >= 0);

    return err ? err : argcnt;
}

int8_t get_stats(char *fname, int8_t mode, int8_t month)
{
    FILE *inpf = fopen(fname, "r");

    if (inpf == NULL)
    {
        printf("ERROR opening file <%s>\n", fname);
    }
    else
    {
        int8_t arg_cnt = 0;
        uint32_t line_cnt = 0;
        uint32_t f_size = 0;
        f_size = rows_count(inpf); 
        rewind(inpf);
        sensor_data *rows = NULL;
        rows = (sensor_data *)malloc((f_size + 1) * sizeof(sensor_data));

        do
        {
            arg_cnt = get_row(inpf, &rows[line_cnt]);
            ++line_cnt;
            if (arg_cnt == 6 || arg_cnt == -1)
            {
            }
            else
            {
                printf("ERROR at line  N%d\n\n", line_cnt);
            }
        } while (arg_cnt >= 0);

        stat_print(rows, line_cnt, month);
        free(rows); 
    }
    fclose(inpf);
    return 0;
}

int32_t rows_count(FILE *fl)
{
    char c = 0;
    int32_t count = 0;

    while ((c = fgetc(fl)) != EOF)
    {
       if(c == '\n')
       {
        ++count;
       }
    }
   return count;
}

int8_t stat_print(sensor_data *rows, uint16_t r_cnt, uint8_t month)
{
    int8_t t_max, t_min, tmp;
    int32_t summ = 0;
    t_max = t_min = rows[0].temp;
    stat *t_stat;

    if (month == 0)
    {
        t_stat = (stat *)malloc(12 * sizeof(stat));
        uint16_t cnt = 0;
        for (int i = 0; i < r_cnt; ++i)
        {
            tmp = rows[i].temp;
            if (tmp > -100 && tmp < 100)
            {
                summ += tmp;
                if (t_max < tmp)
                {
                    t_max = tmp;
                }
                if (t_min > tmp)
                {
                    t_min = tmp;
                }
                ++cnt;

                if (cnt > 0)
                {
                    t_stat[rows[i].month].average = (float)summ / cnt;
                    t_stat[rows[i].month].min = t_min;
                    t_stat[rows[i].month].max = t_max;
                }
            }
        }

        free(t_stat);
    }
    else
    {
    }
    return 0;
}
