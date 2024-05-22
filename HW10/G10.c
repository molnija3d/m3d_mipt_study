/*
Самое длинное слово
В файле input.txt дана строка слов, разделенных пробелами.
Найти самое длинное слово и вывести его в файл output.txt.
Случай, когда самых длинных слов может быть несколько, не обрабатывать.
Input format
Строка из английских букв и пробелов. Не более 1000 символов.
Output format
Одно слово из английских букв.
 */
#include <stdio.h>

int strinp(FILE *inp,char* str);
int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN = 1001};
    char str[STRLEN];
    int str_len = 0, max1 = 0, max2 = 0, pos1 = 0, tmp = 0;
    str_len = strinp(inp,str);

    for(int i=0; i < str_len;)
    {
        while(i < str_len && str[i++] != ' ')
        {
            tmp++;
        }
        if(tmp > max1)
        {
            max1 = tmp;
            pos1 = i - tmp-1;
            if(pos1 < 0)
            {
                pos1 = 0;
            }
        }
        else if(tmp > max2)
        {
            max2 = tmp;
        }
        tmp=0;
    }
    if(max1 > max2)
    {
        for(int i = pos1; i < pos1 + max1; i++)
        {
            fputc(str[i], out);
        }
    }

    fclose(inp);
    fclose(out);
    return 0;
}

int strinp(FILE *inp, char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ')) //in auto test there are only letters and spacebar
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}

