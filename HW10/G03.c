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

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN=1001};
    char str[STRLEN]= {'\0'};
    char last=0;
    int last_idx=0;
   
    
    fscanf(inp,"%[a-zA-Z0-9 ]s",str);
    fclose(inp);
    for(int i = 0; i< STRLEN && str[i]!= '\0'; i++)
     {
      last = str[i];
      last_idx=i;
     }

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
