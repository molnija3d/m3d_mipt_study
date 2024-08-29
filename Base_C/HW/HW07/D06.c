#include <stdio.h>
#include <inttypes.h>
/*
Дана строка заканчивающаяся символом точка '.' Напечатать строку наоборот. Реализуйте рекурсивную функцию, которая считывает и печатает строку наоборот.
void reverse_string()
*/
void reverse_string();

int main(void)
{
    reverse_string();
    return 0; 
}

void reverse_string()
{
    char c;
    if((c = getchar()) != '.')
      {
        reverse_string();  
        printf("%c",c);
      }
}
