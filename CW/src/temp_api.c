#include <stdlib.h>
#include "temp_api.h"


/*
PARSE DATA PER ROWS
*/
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
                err = argcnt + 1;
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
                    data->year = 0;
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
                    data->year = 0;
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
                    data->year = 0;
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
                    data->year = 0;
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
                    data->year = 0;
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
                    data->year = 0;
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

int8_t get_stats(char *fname, int8_t month)
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
                printf("ERROR %d at line N%d\n", arg_cnt, line_cnt);
            }
        } while (arg_cnt >= 0);

        stat_print(rows, line_cnt - 1, month);
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
        if (c == '\n')
        {
            ++count;
        }
    }
    return count;
}

int8_t stat_print(sensor_data *rows, uint32_t r_cnt, uint8_t month)
{
    int8_t yr_t_max, yr_t_min, tmp;
    uint8_t cur_month = 13;
    int32_t m_summ = 0, y_summ = 0;
    yr_t_max = yr_t_min = rows[0].temp;
    stat *m_stat;

    if (month == 0)
    {
        m_stat = (stat *)malloc(12 * sizeof(stat));
        uint16_t m_cnt = 0;
        uint32_t y_cnt = 0;
        for (int i = 0; i < r_cnt; ++i)
        {
            if (rows[i].year)
            {
                tmp = rows[i].temp;
                if (cur_month != (rows[i].month - 1))
                {
                    if (i > 0)
                    {
                        if (m_cnt > 0)
                        {
                            m_stat[cur_month].average = (float)m_summ / m_cnt;
                        }
                        printf("\r\nSTAT IN %2d MONTH:\n", cur_month + 1);
                        printf("  MIN temp = %d", m_stat[cur_month].min);
                        printf("  MAX temp = %d", m_stat[cur_month].max);
                        printf("  AVG temp = %3.2f\n", m_stat[cur_month].average);
                    }
                    cur_month = rows[i].month - 1;
                    m_stat[cur_month].min = rows[i].temp;
                    m_stat[cur_month].max = rows[i].temp;
                    m_cnt = 0;
                    m_summ = 0;
                }

                if (tmp > -100 && tmp < 100)
                {
                    m_summ += tmp;
                    y_summ += tmp;
                    ++m_cnt;
                    ++y_cnt;

                    if (yr_t_max < tmp)
                    {
                        yr_t_max = tmp;
                    }
                    if (yr_t_min > tmp)
                    {
                        yr_t_min = tmp;
                    }

                    if (m_stat[cur_month].max < tmp)
                    {
                        m_stat[cur_month].max = tmp;
                    }
                    if (m_stat[cur_month].min > tmp)
                    {
                        m_stat[cur_month].min = tmp;
                    }
                }
            }
        }
        printf("\nStats for %d year:\n", rows[0].year);
        printf("   MAX temp = %d", yr_t_max);
        printf("   MIN temp = %d", yr_t_min);
        printf("   AVG temp = %2.2f\n", (float)y_summ / y_cnt);
        free(m_stat);
    }
    return 0;
}
