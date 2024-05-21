/*
Заканчивается на a
В файле input.txt дано предложение. Необходимо определить, сколько слов заканчиваются на букву 'а'. Ответ записать в файл output.txt.
Input format
Строка из английских букв и пробелов не более 1000 символов.
Output format
Одно целое число
 */
#include <stdio.h>

int strinp(FILE *inp, char* str);

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN = 1001};
    char str[STRLEN];
    int str_len = 0, cnt = 0;

    str_len = strinp(inp,str);
    fclose(inp);

    printf("%s\n",str);
    for(int i = 0; i < str_len;)
    {

        while(i < str_len && str[i++] != ' ');
        if(i < str_len && str[i - 2] == 'a')
        {
            cnt++;
        }
        else if(i == str_len && str[i-1] == 'a')
        {
            cnt++;
        }
    }
    fprintf(out, "%d", cnt);
    fclose(out);
    return 0;
}

int strinp(FILE *inp, char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if((c >= 'A' && c <='Z') || (c >= 'a' && c <='z') || (c == ' ')) //in auto test there are only letters and spacebar
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}
