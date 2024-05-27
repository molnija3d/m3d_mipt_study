#include "temp_functions.h"

int8_t get_data_row(FILE *inp, sensor_data *data)
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
                    printf("Wrong YEAR %d\n", num);
                    err = 1;
                }
                break;
            case 1:
                if (num > 0 && num < 13)
                {
                    data->month = num;
                }
                else
                {
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
                    printf("Wrong TEMP %d\n", num);
                    err = 6;
                }
                break;
            default:
                err = 7;
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
            else
            {
            }
            num = 0;
        }
        else if (c == ' ')
        {
        }
        else
        {
            err = 8;
        }

    } while (c != '\n' && err >= 0);

    return err ? err : argcnt;
}

int8_t get_stats(char *fname, int8_t mode, int8_t month)
{
    FILE *inpf = fopen(fname, "r");
    int8_t arg_cnt = 0;
    int32_t line_cnt = 0;
    int pos = 0;
    sensor_data row;

    if (inpf == NULL)
    {
        printf("ERROR opening file <%s>\n", fname);
    }
    else
    {

        stat stats;
        stats.average = 0.f;
        stats.min = 100;
        stats.max = -100;
        do
        {
            arg_cnt = get_data_row(inpf, &row);
            ++line_cnt;
            if (arg_cnt == 6 || arg_cnt == -1)
            {
                stat_calc(&stats, row, month);
            }
            else
            {
                printf("ERROR at line  N%d\n\n", line_cnt);
            }

        } while (arg_cnt >= 0);
        if (month == 0)
        {
            printf("Stats for %d year:\nAVERAGE temp = %2.2f\nMIN temp = %d\nMAX temp = %d", row.year, stats.average, stats.min, stats.max);
        }
        else
        {
            printf("Stats for %d month:\nAVERAGE temp = %2.2f\nMIN temp = %d\nMAX temp = %d", month, stats.average, stats.min, stats.max);
        }

        fclose(inpf);
    }
    return 0;
}

int8_t stat_calc(stat *s_month, sensor_data row, int8_t month)
{
    static int32_t summ = 0;
    static int32_t cnt = 0;
    if (month == 0)
    {
        summ += row.temp;
        s_month->average = (float)summ / ++cnt;
        if (s_month->min > row.temp)
        {
            s_month->min = row.temp;
        }
        else
        {
        }

        if (s_month->max < row.temp)
        {
            s_month->max = row.temp;
        }
        else
        {
        }
    }
    else if (month == row.month)
    {
        summ += row.temp;
        s_month->average = (float)summ / ++cnt;
        if (s_month->min > row.temp)
        {
            s_month->min = row.temp;
        }
        else
        {
        }

        if (s_month->max < row.temp)
        {
            s_month->max = row.temp;
        }
        else
        {
        }
    }
    else
    {
    }
    return 0;
}
