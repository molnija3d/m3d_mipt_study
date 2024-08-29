/*
Изменить расширение
В файле input.txt записан полный адрес файла (возможно, без расширения).
Необходимо изменить его расширение на ".html" и записать результат в файл output.txt.
Input format
Строка состоящая из символов: a-z, A-Z, 0-9, /
Output format
Исходная строка с измененным расширением.
 */
#include <stdio.h>


int strinp(FILE *inp,char* str);
void ext_html(char *addr, int len);

int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");
    char addr[str_len] = {'\0'};
    int len = 0;

    len = strinp(inp,addr);
    ext_html(addr, len);
    fprintf(outp, "%s", addr);

    fclose(inp);
    fclose(outp);

    return 0;
}

void ext_html(char *addr, int len)
{
    char html[] = ".html";
    int dot_idx = -1;
    for(int i = len-1; i >= 0 && addr[i] != '/'; i--)
    {
        if(addr[i] == '.')
        {
            dot_idx = i;
            i = -1;
        }
    }

    if(dot_idx == -1)
    {
        dot_idx = len;
    }

    for(int i=0; i < 6; i++)
    {
        addr[dot_idx+i] = html[i];
    }
}

int strinp(FILE *inp, char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '/') || (c == '.')) //in auto test there are only letters, '.' and '/'
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}
