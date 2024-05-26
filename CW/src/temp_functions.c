#include "temp_functions.h"

sensor_data get_sensor_data(FILE *inp)
{
    sensor_data data_str;
    return data_str;
}
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
                printf("Wrong '-' symbol at ARG №%d\n", argcnt);
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

    switch (err)
    {
    case 1:
        printf("Wrong YEAR\n");
        break;
    case 2:
        printf("Wrong MONTH\n");
        break;
    case 3:
        printf("Wrong DAY\n");
        break;
    case 4:
        printf("Wrong HOURS\n");
        break;
    case 5:
        printf("Wrong MINUTES\n");
        break;
    case 6:
        printf("Wrong TEMP\n");
        break;
    case 7:
        break;
    case 8:
        break;
    case -1:
    case 0:
    default:
    }

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
        switch (mode)
        {
        case FULL:
            stat s_year;

        case MONTH:
            stat s_month;
            s_month.average = 0.f;
            s_month.min = 100;
            s_month.max = -100;
            do
            {
                arg_cnt = get_data_row(inpf, &row);
                ++line_cnt;
                if (arg_cnt == 6 || arg_cnt == -1)
                {
                    stat_month(&s_month, row, month);
                }
                else
                {
                    printf("ERROR at line  №%d\n", line_cnt);
                }

            } while (arg_cnt >= 0);
            printf("Stats for %d month:\nAVERAGE temp = %2.2f\nMIN temp = %d\nMAX temp = %d", month, s_month.average, s_month.min, s_month.max);

            break;
        }
        fclose(inpf);
    }
    return 0;
}

int8_t stat_month(stat *s_month, sensor_data row, int8_t month)
{
    static float summ = 0.f;
    static int32_t cnt = 0;
    if (month == row.month)
    {
        summ += row.temp;
        s_month->average = summ / ++cnt;
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