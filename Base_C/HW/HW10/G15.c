/*
Cao заменить на Ling
В файле input.txt дано предложение. Необходимо заменить все имена «Cao» на «Ling» и записать результат в файл output.txt.
Input format
Строка из английский букв, знаков препинания и пробелов. Не более 1000 символов.
Output format
Строка из английский букв, знаков препинания и пробелов.
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN = 4};
    char buff[4] = {'\0'};
    char c = 0;
    int i = 0;

    while((c = fgetc(inp)) != EOF)
    {
        if(c == 'o')
        {
            if(((ftell(inp)) > 2) && (!fseek(inp, -3, SEEK_CUR)))
            {
                do
                {
                    c = fgetc(inp);
                    buff[i++] = c;
                }
                while(i < 3);
                i = 0;
                if(!strcmp(buff,"Cao"))
                {
                    if(!fseek(out, -2, SEEK_CUR))
                    {
                        fputs("Ling", out);
                    }
                }
                else
                {
                    fputc(c, out);
                }
            }
            else
            {
                fputc(c, out);
            }
        }
        else
        {
            fputc(c, out);
        }
    }
    fclose(inp);
    fclose(out);
    return 0;
}
