/*
Удалить пробелы из текста
В файле input.txt необходимо удалить все лишние пробелы (в начале предложения и сдвоенные пробелы).
Для решения задачи разработать функцию. Результат записать в output.txt.
Input format
Строка из английских букв, знаков препинания и пробелов. Не более 1000 символов.
Output format
Строка из английских букв, знаков препинания и пробелов.
 */
#include <stdio.h>
#include <string.h>
int strinp(FILE *inp,char* str);
void delspb(char *in, char *out,int str_len);

int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");
    char strin[str_len] = {'\0'};
    char strout[str_len] = {'\0'};

    strinp(inp, strin);
    delspb(strin, strout, str_len);
    fclose(inp);

    fprintf(outp, "%s", strout);
    fclose(outp);

    return 0;
}

void delspb(char *in, char *out,int str_len)
{
    int j = 0;
    for(int i = 0; i< str_len; i++)
    {
        if(i==0 && in[i] == ' ')
        {
            while(in[++i] == ' ');
            out[j++] = in[i];
        }
        else
        if(i > 0 && in[i-1] == ' ' && in[i]!=' ')
        {
            out[j++] = ' ';
            out[j++] = in[i];
        }
        else
        if(in[i] != ' ')
        {
            out[j++] = in[i];
        }
    }
}

int strinp(FILE *inp, char* str)
{
    int res = 0;
    res = fscanf(inp,"%[a-zA-Z0-9 ,.;:!?-\'\")(]s", str);
    return res;
}
