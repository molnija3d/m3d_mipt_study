/*
Равносторонние треугольники
Cia очень любит равносторонние треугольники. Он все время выкладывает их из камней. Ling дал Cia камни и попросил его составить такой треугольник если это возможно.
Помогите Cia сложить треугольник используя все камни или напечатайте слов NO, если это невозможно. Пример треугольников, которые составляет Cia:
 *
* *

  *
 * *
* * *

   *
  * *
 * * *
* * * *
Во входном файле input.txt записано некоторое количество символов * (камней).
Необходимо построить равносторонний треугольник используя все символы * и символ пробел, записать ответ в выходной файл output.txt.
Между соседними символами * строго один пробел.
Если треугольник невозможно составить, используя все камни, то необходимо записать единственное слово NO в файл output.txt.
Input format
Текстовый файл состоит из различных символов и символов *.
Output format
Равносторонний треугольник составленный из символов *, символов пробела и символов переноса строк или слово NO.
*/
#include <stdio.h>

int strinp(FILE *inp,char* str);
_Bool triangle(FILE *outp, int in_len);

int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");
    char in_str[str_len] = {'\0'};
    int in_len = 0;

    in_len = strinp(inp, in_str);

    if(!(in_len && triangle(outp, in_len)))
    {
        fprintf(outp, "NO");
    }
    else
    {
    }

    fclose(inp);
    fclose(outp);

    return 0;
}

int strinp(FILE *inp, char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if(c == '*')
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}

_Bool triangle(FILE *outp, int in_len)
{
    _Bool check = 0;
    int cnt = 1, sum = 0;

    while(sum < in_len)
    {
        sum += cnt++;
    }
    if(sum == in_len)
    {
        check = 1;
        cnt--;
        for(int i = 0; i < cnt; i++)
        {
            for(int j = 0; j < cnt - i - 1; j++)
            {
                fprintf(outp," ");
            }
            
            for(int j = cnt - i - 1; j < cnt + i; j++)
            {
                fprintf(outp,((cnt % 2) ? (i % 2) : !(i % 2)) ? ((j % 2) ? "*":" ") : ((j % 2) ? " ":"*"));
            }
            fprintf(outp,"\n");
        }
    }
    else
    {
        check = 0;
    }
    return check;
}
