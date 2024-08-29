/*
Составить палиндром
Разработать функцию дана строка из маленьких английских букв. Составить из символов палиндром максимальной длинны.
При составлении палиндрома буквы в палиндроме должны быть расположены в лексикографическом порядке. Записать ответ в файл output.txt.
Input format
Строка из маленьких английских букв. Не более 1000 символов.
Output format
Строка из маленьких английских букв.
 */
#include <stdio.h>
int strinp(FILE *inp, char *str);
void make_palindrom(int in_len, char *in_str, char *plndr);

int main(void)
{
    enum
    {
        str_len = 1001
    };
    FILE *inp = fopen("input.txt", "r");
    FILE *outp = fopen("output.txt", "w");

    char in_str[str_len] = {'\0'};
    char palindrom[str_len] = {'\0'};
    int len = 0;

    len = strinp(inp, in_str);
    fclose(inp);

    make_palindrom(len, in_str, palindrom);
    fprintf(outp, "%s", palindrom);
    
    fclose(outp);
    return 0;
}

void make_palindrom(int in_len, char *in_str, char *plndr)
{
    char frq_lttr[26] = {0}, pivot = 0;
    int idx = 0, l_lngth = 0;

    for (int i = 0; i < in_len; ++i)
    {
        ++frq_lttr[in_str[i] - 'a'];
    }

    for (int i = 0; i < 26; ++i)
    {
        if ((frq_lttr[i] % 2) && (pivot == 0))
        {
            pivot = i + 'a';
        }
        for (int j = 0; j < frq_lttr[i] / 2; ++j)
        {
            plndr[idx++] = i + 'a';
        }
    }

    l_lngth = idx;

    if (pivot)
    {
        plndr[idx] = pivot;
    }

    for(int i = 0; i <= l_lngth; ++i)
    {
       plndr[idx++] = plndr[l_lngth - i];
    }
}

int strinp(FILE *inp, char *str)
{
    int i = 0;
    char c = 0;
    while ((c = fgetc(inp)) != EOF)
    {
        if ((c >= 'a' && c <= 'z')) // in auto test there are only small letters
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}