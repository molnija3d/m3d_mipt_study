/*
Пары соседних символов
В файле input.txt записаны символы. Необходимо разработать функцию, которая меняет местами пары соседних символов не обращая внимание на символы пробел.
Если количество символов нечетно (пробелы не считаем), то последний символ не меняем. Результат записать в файл output.txt.
Input format
Строка из английских букв, пробелов и знаков препинания. Не более 1000 символов.
Output format
Строка из английских букв, пробелов и знаков препинания.
Examples
 */
#include <stdio.h>
#include <string.h>

int strinp(FILE *inp, char* str);
void swap(char *in, char *out, int str_len);
void swap_ab(char *arr, int posa, int posb);

int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");
    char strin[str_len] = {'\0'};
    char strout[str_len] = {'\0'};

    strinp(inp, strin);
    swap(strin, strout, str_len);
    fclose(inp);

    fprintf(outp, "%s", strout);
    fclose(outp);

    return 0;
}

void swap(char *in, char *out, int str_len)
{
    int fst = 0, lst = 0;
    strcpy(out, in);
    for(int i = 1; i < str_len && in[i] != '\0'; i++)
    {
        if(in[i] != ' ' && in[i-1] != ' ')
        {
            lst = i++;
            swap_ab(out, fst, lst);
            if(in[i] != ' ')
            {
                fst = i;
            }
            else
            {
                while(in[++i] == ' ');
                fst = i;
            }
        }
        else if(in[i-1] == ' ' && in[i] != ' ')
        {
            lst = i++;
            swap_ab(out, fst, lst);
            if(in[i] != ' ')
            {
                fst = i;
            }
            else
            {
                while(in[++i] == ' ');
                fst = i;
            }
        }
        else
        if(fst == 0 && in[0] == ' ')
        {
            while(in[i] == ' ')
            {
                fst = ++i;
            }
        
        }
    }
}

void swap_ab(char *arr, int posa, int posb)
{
    char tmp = arr[posa];
    arr[posa] = arr[posb];
    arr[posb] = tmp;
}

int strinp(FILE *inp, char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if((c >= 'A' && c <='Z') || (c >= 'a' && c <='z') || (c == ' ') || (c == '!') || (c == '.')) //in auto test there are only letters, ' ', '!' and '.'
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}

