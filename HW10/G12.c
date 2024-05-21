/*
Разобрать на слова
В файле input.txt дано предложение требуется разобрать его на отдельные слова. Напечатать каждое слово на отдельной строке в файл output.txt.
Input format
Одна строка из английских букв и пробелов не более 1000 символов.
Output format
Каждое слово на отдельной строке
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN = 1001};
    char c;
    _Bool prev_spb = 1;

    while((c = fgetc(inp)) != EOF)
    {
        if(c == ' ' && prev_spb == 0)
        {
            prev_spb = 1;
            fputc('\n',out);
        }
        else if((c >= 'a' && c <= 'z') || (c >= 'A' &&  c <= 'Z') || (c >= '0' && c <= '9'))
        {
            prev_spb = 0;
            fputc(c,out);
        }
    } 
    fclose(inp);
    fclose(out);
    return 0;
}
