/*
Количество букв
В файле input.txt считать символьную строку, не более 10 000 символов.
Посчитать количество строчных (маленьких) и прописных (больших) букв в введенной строке.
Учитывать только английские буквы. Результат записать в файл output.txt.
Input format
Строка состоящая из английских букв, цифр, пробелов и знаков препинания.
Output format
Два целых числа. Количество строчных букв и количество заглавных букв.
 */
#include <stdio.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    char c = 0;
    int cnt_s = 0, cnt_b = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if(c >= 'a' && c <= 'z')
        {
            cnt_s++;
        }
        else if(c >= 'A' && c <= 'Z')
        {
            cnt_b++;
        }
    }
    fclose(inp);
    fprintf(out, "%d %d", cnt_s, cnt_b);
    fclose(out);
    return 0;
}
