/*
Проверка на палиндром
В файле input.txt символьная строка не более 1000 символов. 
Необходимо проверить, является ли она палиндромом (палиндром читается одинаково в обоих направлениях). 
Реализовать логическую функцию is_palindrom(str) и записать ответ в файл output.txt.
Input format
Строка из заглавных английских букв
Output format
YES или NO
 */
#include <stdio.h>

int strinp(FILE *inp,char* str);
int is_palindrom(char *str,int len);

int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");
    char strin[str_len]= {'\0'};
    int len = strinp(inp, strin);
    fprintf(outp,"%s",is_palindrom(strin, len) ? "YES":"NO");
    fclose(inp);
    fclose(outp);

    return 0;
}

int is_palindrom(char *str,int len)
{
   _Bool flag=1;
   for(int i = 0; i + i < len && flag; i++)
   {
     if(str[i]!=str[len-i-1])
      flag=0;
   }
   return flag;
}

int strinp(FILE *inp,char* str)
{
    int i = 0;
    char c = 0;
    while((c=fgetc(inp))!=EOF)
    {
        if((c >= 'a' && c <='z') || (c >= 'A' && c <='Z'))
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}
