#include <stdio.h>
#include <inttypes.h>
/*
Дана строка из английских символов, пробелов и знаков препинания. В конце строки символ точка.
Необходимо реализовать рекурсивную функцию, которая считывает данную строку со стандартного потока ввода и
возвращает целое число - количество символов 'a' в данной строке.
int acounter(void)
Используя данную функцию решить задачу.
*/
int acounter(void);

int main(void)
{
    printf("%d\n",acounter());
    return 0;
}

int acounter(void)
{
    int i = 0;
    char c;
    if ((c=getchar())!='.')
    {
      i += acounter();
        if (c == 'a')
            ++i;
    }
    return i;
}
