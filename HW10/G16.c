/*
Ling заменить на Cao
В файле input.txt дано предложение. Необходимо заменить все имена «Ling» на «Cao» и результат записать в файл output.txt.
Input format
Строка из английских букв, пробелов и знаков препинания. Не более 1000 символов.
Output format
Строка из английских букв, пробелов и знаков препинания.
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    char buff[5] =  {'\0'};
    char c = 0;
    int i = 0;

    while((c = fgetc(inp)) != EOF)
    {
        if(c == 'g')
        {
            if(((ftell(inp)) > 3) && (!fseek(inp, -4, SEEK_CUR)))
            {
                do
                {
                    c = fgetc(inp);
                    buff[i++] = c;
                }
                while(i < 4);
                i = 0;
                if(!strcmp(buff, "Ling"))
                {
                    if(!fseek(out, -3, SEEK_CUR))
                    {
                        fputs("Cao", out);
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
