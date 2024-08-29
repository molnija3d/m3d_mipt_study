/*
Soundex
Известный алгоритм Soundex (https://ru.wikipedia.org/wiki/Soundex) определяет, похожи ли два английских слова по звучанию.
а вход он принимает слово и заменяет его на некоторый четырёхсимвольный код. Если коды двух слов совпадают, то слова, как правило, звучат похоже.

Вам требуется реализовать этот алгоритм. Он работает так:

Первая буква слова сохраняется.
В остальной части слова:
буквы, обозначающие, как правило, гласные звуки: a, e, h, i, o, u, w и y — отбрасываются; оставшиеся буквы (согласные) заменяются на цифры от 1 до 6,
причём похожим по звучанию буквам соответствуют одинаковые цифры:
1: b, f, p, v
2: c, g, j, k, q, s, x, z
3: d, t
4: l
5: m, n
6: r
Любая последовательность одинаковых цифр сокращается до одной такой цифры. Итоговая строка обрезается до первых четырёх символов.
Если длина строки меньше требуемой, недостающие символы заменяются знаком 0.
Примеры:
аmmonium > ammnm > a5555 > a5 > a500
implementation > implmnttn > i51455335 > i514535 > i514
Input format
Во входном файле input.txt находится одно непустое слово, записанное строчными латинскими буквами. Длина слова не превосходит 20 символов.
Output format
Напечатайте четырёхбуквенный код, соответствующий слову в файл output.txt.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strinp(FILE *inp, char* str);

int soundex(char* in_str, int len, char *sndx);

int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");
    char in_str[str_len] = {'\0'};
    int in_len = 0;

    in_len = strinp(inp, in_str);
    fclose(inp);
    
    char *sndx = (char *) malloc (in_len * sizeof(char));
    memset(sndx, 0, in_len * sizeof(char));

    soundex(in_str, in_len, sndx);

    fprintf(outp, "%s", sndx);   
    fclose(outp);

    return 0;
}
int soundex(char* in_str, int len, char *sndx)
{
    char c = 0, tmp[len];
    int t_idx = 0, p_idx = 0;
    sndx[0] = tmp[t_idx++] = in_str[0];// - 0x20;
    for(int i = 1; i < len; i++)
    {
        c = in_str[i];
        switch(c)
        {
        case 'b':
        case 'f':
        case 'p':
        case 'v':
        {
            tmp[t_idx++] = '1';
        }
        break;

        case 'c':
        case 'g':
        case 'j':
        case 'k':
        case 'q':
        case 's':
        case 'x':
        case 'z':
        {
            tmp[t_idx++] = '2';
        }
        break;

        case 'd':
        case 't':
        {
            tmp[t_idx++] = '3';
        }
        break;

        case 'l':
        {
            tmp[t_idx++] = '4';
        }
        break;

        case 'm':
        case 'n':
        {
            tmp[t_idx++] = '5';
        }
        break;

        case 'r':
        {
            tmp[t_idx++] = '6';
        }
        break;
        }
    }
    p_idx = 1;
    for(int i = 1; i < t_idx; i++)
    {
        if(tmp[i] != tmp[i+1])
        {
            sndx[p_idx++] = tmp[i];
        }
    }
    if(p_idx < 4)
    {
        for(int i = p_idx; i < 4; i++)
        {
            sndx[i] = '0';
        }
    }
    else if(p_idx > 4)
    {
        for(int i = 4; i < len; i++)
        {
            sndx[i] = '\0';
        }
    }
    return p_idx;
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
