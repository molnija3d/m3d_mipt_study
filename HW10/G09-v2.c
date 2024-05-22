/*
Удалить повторяющиеся символы
В файле input.txt строка из меленьких и больших английских букв, знаков препинания и пробелов. 
Требуется удалить из нее повторяющиеся символы и все пробелы. Результат записать в файл output.txt.
Input format
Строка из меленьких и больших английских букв, знаков препинания и пробелов. Размер строки не более 1000 сивмолов.
Output format
Строка из меленьких и больших английских букв.
 */
#include <stdio.h>
int strinp(FILE *inp,char* str);

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN = 1001};
    char str[STRLEN];
    int str_len = 0,cnt = 0;
    str_len = strinp(inp, str);
  
    for(int i = 0; i < str_len;i++)
    {
        for(int j = i; j>=0;j--)
        {
         if(str[j] == str[i])
          {
          cnt++;
          }
        }
        
        if(cnt == 1  && str[i] != ' ')
        {
         fprintf(out,"%c",str[i]);
        }
         cnt = 0;        
    }

    fclose(inp);
    fclose(out);
    return 0;
}

int strinp(FILE *inp,char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if((c >= 'A' && c <='Z') || (c >= 'a' && c <='z')) //in auto test there are only letters
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}

