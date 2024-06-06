#include "temp_api.h"

/*
PARSE DATA PER ROWS
*/
int8_t free_rows(sensor_data **list)
{
    while (*list)
    {
        sensor_data *tmp = *list;
        *list = (*list)->prev;
        free(tmp);
    }
    return 0;
}
int8_t parse_row(FILE *inp, sensor_data **data)
{
    int8_t err = 0;
    int16_t num = 0;
    int8_t sign = 1;
    int8_t argcnt = 0;
    char c = 0;
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
                    (*data)->year = num;
                }
                else
                {
                    (*data)->year = 0;
                    err = 1;
                }
                break;
            case 1:
                if (num > 0 && num < 13)
                {
                    (*data)->month = num;
                }
                else
                {
                    (*data)->year = 0;
                    err = 2;
                }
                break;
            case 2:
                if (num > 0 && num < 32)
                {
                    (*data)->day = num;
                }
                else
                {
                    (*data)->year = 0;
                    err = 3;
                }
                break;
            case 3:
                if (num >= 0 && num < 25)
                {
                    (*data)->hr = num;
                }
                else
                {
                    (*data)->year = 0;
                    err = 4;
                }
                break;
            case 4:
                if (num >= 00 && num < 61)
                {
                    (*data)->min = num;
                }
                else
                {
                    (*data)->year = 0;
                    err = 5;
                }
                break;
            case 5:
                if (num > -100 && num < 100)
                {
                    (*data)->temp = sign * num;
                }
                else
                {
                    (*data)->year = 0;
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
int8_t add_data(FILE *inp, sensor_data **curr)
{
    int8_t err = 0;
    static _Bool data_ok = 1;
    if (data_ok)
    {
        sensor_data *data;
        data = malloc(sizeof(sensor_data));
        data->prev = NULL;
        data->next = NULL;
        if (*curr)
        {
            (*curr)->next = data;
            data->prev = *curr;
            *curr = data;
        }
        else
        {
            data->prev = *curr;
            *curr = data;
        }
    }

    err = parse_row(inp, curr);
    
    if (err == 6 || err == -1)
    {
        data_ok = 1;
    }
    else
    {
        data_ok = 0;
    }
    
    return err;
}

int8_t get_stats(params my_param)
{
    FILE *inpf = fopen(my_param.file, "r");

    if (inpf == NULL)
    {
        printf("ERROR opening file <%s>\n", my_param.file);
    }
    else
    {
        int8_t arg_cnt = 0;
        uint32_t row_cnt = 0;
        uint32_t cur_pos = 0;
        uint32_t f_size = 0;
        sensor_data *rows = NULL;
        do
        {
            arg_cnt = add_data(inpf, &rows);
            ++row_cnt;
            ++cur_pos;
            if (arg_cnt != 6 && arg_cnt != -1)
            {
                printf("ERROR %d at line N%d\n", arg_cnt, row_cnt);
                --cur_pos;
            }
        } while (arg_cnt >= 0);
        //   qsort(rows, (size_t)(cur_pos - 1), sizeof(sensor_data), compare_rows);
        rows = rows->prev;
        stat_print_list(&rows, my_param.month);
        free_rows(&rows);
    }

    fclose(inpf);
    return 0;
}
int8_t del_row(sensor_data *data, int32_t row_id)
{
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

int8_t stat_print_list(sensor_data **rows, uint8_t month)
{
    int8_t tmp;
    int32_t m_summ = 0, y_summ = 0;
    stat *m_stat;
    m_stat = (stat *)malloc(12 * sizeof(stat));
    for (int i = 0; i < 12; ++i)
    {
        m_stat[i].stored = 0;
    }
    uint16_t m_cnt = 0;

    if (month == 0)
    {
        int32_t y_summ = 0;
        uint8_t cur_month = 13;
        int8_t yr_t_max, yr_t_min;
        uint32_t y_cnt = 0;
        yr_t_max = yr_t_min = (*rows)->temp;

        while ((*rows)->prev)
        {
            tmp = (*rows)->temp;
            if (cur_month != ((*rows)->month - 1))
            {
                if (m_cnt > 0)
                {
                    m_stat[cur_month].average = (float)m_summ / m_cnt;
                }
                cur_month = (*rows)->month - 1;
                m_cnt = 0;
                m_summ = 0;
                m_stat[cur_month].min = tmp;
                m_stat[cur_month].max = tmp;
                m_stat[cur_month].stored = 1;
            }

            m_summ += tmp;
            y_summ += tmp;
            ++m_cnt;
            ++y_cnt;

            m_stat[cur_month].average = (float)m_summ / m_cnt;

            if (m_stat[cur_month].max < tmp)
            {
                m_stat[cur_month].max = tmp;
            }
            if (m_stat[cur_month].min > tmp)
            {
                m_stat[cur_month].min = tmp;
            }
            if (yr_t_max < tmp)
            {
                yr_t_max = tmp;
            }
            if (yr_t_min > tmp)
            {
                yr_t_min = tmp;
            }
            *rows = (*rows)->prev;
        }
        print_header(H_MONTH);
        for (int i = 0; i < 12; ++i)
        {
            print_month(m_stat, i);
        }
        if ((*rows)->year != 0)
        {
            print_header(H_YEAR);
            printf("| %d | %+3d |", (*rows)->year, yr_t_min);
            printf(" %+3d |", yr_t_max);
            printf(" %+5.1f |\n", (float)y_summ / y_cnt);
            printf("----------------------------\n");
        }
        else
        {
            printf("\r-----------------------------------------\n");
            printf("\r\n=========================================\n");
            printf("STATS for --> %d <-- YEAR:\n", (*rows)->year);
            printf("=========================================\n");
            printf("|!!--->>>  NO DATA FOR THIS YEAR  <<<---!!|");
        }
    }
    else
    {
        m_cnt = 0;
        m_summ = 0;
        m_stat[month - 1].max = -99;
        m_stat[month - 1].min = 99;

        while ((*rows)->prev)
        {
            tmp = (*rows)->temp;
            if (month == ((*rows)->month))
            {
                m_summ += tmp;
                ++m_cnt;

                if (m_stat[month - 1].max < tmp)
                {
                    m_stat[month - 1].max = tmp;
                }
                if (m_stat[month - 1].min > tmp)
                {
                    m_stat[month - 1].min = tmp;
                }
            }
            *rows = (*rows)->prev;
        }

        if (m_cnt > 0)
        {
            m_stat[month - 1].average = (float)m_summ / m_cnt;
            m_stat[month - 1].stored = 1;
        }
        print_header(H_MONTH);
        print_month(m_stat, month - 1);
    }
    free(m_stat);
    return 0;
}
void print_header(uint8_t hdr)
{
    switch (hdr)
    {
    case H_MONTH:
        printf("\r-------------------------------------\n");
        printf("|    MONTH    |  MAX |  MIN |  AVG  |\n");
        printf("-------------------------------------\n");
        break;
    case H_YEAR:
        printf("\r\n============================\n");
        printf("| YEAR | MAX | MIN |  AVG  |\n");
        printf("----------------------------\n");
        break;
    }
}

int8_t print_month(stat *m_stat, int8_t cur_month)
{
    uint8_t err = 0;
    if (m_stat[cur_month].stored != 0)
    {

        printf("|  %9s  |", num_to_str(cur_month));
        printf("  %+3d |", m_stat[cur_month].max);
        printf("  %+3d |", m_stat[cur_month].min);
        printf(" %+5.1f |\n", m_stat[cur_month].average);
        printf("\r-------------------------------------\n");
    }
    else
    {
        err = cur_month;
        printf("-------------------------------------------\n");
        printf("\r\nSTATS FOR --> %s <-- MONTH:\n", num_to_str(cur_month));
        printf("-------------------------------------------\n");
        printf("|!!!--->>> NO DATA FOR THIS MONTH <<<---!!!|\n");
    }
    return err;
}
const char *num_to_str(uint8_t month)
{
    static const char months[12][10] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
    return months[month];
}

int32_t compare_rows(const void *av, const void *bv)
{
    sensor_data *a = (sensor_data *)av;
    sensor_data *b = (sensor_data *)bv;
    int32_t res = 0;
    if (a->year != b->year)
    {
        res = a->year - b->year;
    }
    else if (a->month != b->month)
    {
        res = a->month - b->month;
    }
    else if (a->day != b->day)
    {
        res = a->day - b->day;
    }
    else if (a->hr != b->hr)
    {
        res = a->hr - b->hr;
    }
    else if (a->min != b->min)
    {
        res = a->min - b->min;
    }
    else
    {
        res = 0;
    }
    return res;
}


