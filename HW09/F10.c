/*
Упаковать строку
Дана строка состоящая из маленьких латинских букв 'a'..'z'. В конце строки точка. 
Необходимо заменить повторяющиеся буквы на <буква><количество повторений>
Input format
Входная строка состоящая из букв 'a'-'z' не превышающая 1000 символов. В конце строки символ '.'
Output format
Результат состоящий из букв и чисел, без пробелов
*/
#include <stdio.h>

void archStr(void);

int main(void)
{
    archStr();
    return 0;
}

void archStr(void)
{
    char c,prev;
    int cnt=1;
    prev=getchar();
    do
     {
      c=getchar();
      if(c == prev)
       ++cnt;
      else
      {
       printf("%c%d",prev,cnt);
       prev=c;
       cnt=1;
      }
     }
    while(c!='.'); 
}

