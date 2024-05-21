/*
Последний номер символа
В файле input.txt дана строка из 1000 символов. Показать номера символов, совпадающих с последним символом строки. 
Результат записать в файл output.txt
Input format
Строка не более 1000 символов
Output format
Целые числа через пробел - номера символа, который совпадает с последним символом строки.
 */
#include <stdio.h>
#include <string.h>
int strinp(FILE *inp,char* str);

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN=1001};
    char str[STRLEN]= {'\0'};
    char last=0;
    int last_idx=0;
   
    last_idx = strinp(inp,str) - 1;
    last = str[last_idx];
    fclose(inp);
    
    for(int i=0; i<last_idx; i++)
    {
     if(str[i] == last)
      {
       fprintf(out,"%d ",i);
      }
    }
    fclose(out);
    return 0;
}

int strinp(FILE *inp,char* str)
{
    int i = 0;
    char c = 0;
    while((c=fgetc(inp))!=EOF)
    {
        if((c >= 'a' && c <='z') || (c >= '0' && c <='9'))
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}
