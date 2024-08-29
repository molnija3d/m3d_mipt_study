/*
Проверка на палиндром
Считать предложение из файла input.txt и определить можно ли из английских букв предложения записанного в файле получить одно слово - палиндром.
Ответ напечатать на стандартный поток вывода. Требуется реализовать логическую функцию и применить ее.
is_palindrom(string)
Input format
Строка из маленьких английских букв и пробелов. Не более 1000 символов.
Output format
YES или NO
 */
#include <stdio.h>


int strinp(FILE *inp, char* str);
_Bool is_palindrom(char *in_str, int str_len);


int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt", "r");
    char in_str[str_len] = {'\0'};
    int in_len;
    in_len = strinp(inp, in_str);
    fclose(inp);

    printf("%s", is_palindrom(in_str, in_len) ? "YES":"NO");
    return 0;
}
_Bool is_palindrom(char *inp_str, int str_len)
{
    _Bool flag = 1;
    int odd = 0, cnt = 0;
    char c = 0;

    for(int i = 0; inp_str[i] != '\0' && i < str_len && flag; i++)
    {
        cnt = 0;
        c = inp_str[i];
        for(int j = 0; inp_str[j] != '\0' && j < str_len && flag; j++)
        {
            if (c == inp_str[j])
            {
                cnt++;
            }
        }
        if(cnt % 2)
        {
            odd++;
            if(odd > 1)
            {
                flag = 0;
            }
        }
    }
    return flag;
}


int strinp(FILE *inp, char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if(c >= 'a' && c <= 'z')
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}


