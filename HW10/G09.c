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
#include <string.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN=1001};
    char str[STRLEN];
    int str_len=0,cnt=0;
    fscanf(inp,"%[0-9a-zA-Z ,.?!:;\"\"\'\']s",str);
    str_len=strlen(str);
    for(int i=0; i<str_len;i++)
    {
        for(int j=i; j>=0;j--)
        {
         if(str[j] == str[i])
          {
          cnt++;
          }
        }
   //     printf("%d  %c\n",cnt,str[i]);
        if(cnt == 1  && str[i] != ' ')
        {
         fprintf(out,"%c",str[i]);
        }
        
         cnt = 0;
        
    }
    printf("%s",str);
   
    fclose(inp);

    fclose(out);
    return 0;
}
