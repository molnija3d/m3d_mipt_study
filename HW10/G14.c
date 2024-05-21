/*
Hello name
В файле input.txt в одной строке фамилию, имя и отчество. Сформировать файл приветствие output.txt, где останутся имя и фамилия
Input format
Строка состоящая из английских букв и пробелов не более 100 символов. Формат: Фамилия Имя Отчество
Output format
Строка состоящая из английских букв и пробелов
 */
#include <stdio.h>

int main(void)
{
    FILE *inp = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    enum {STRLEN = 101};
    char name[STRLEN] = {'\0'};
    char surname[STRLEN] = {'\0'};

    fscanf(inp, "%s%s", surname, name);
    fclose(inp);

    fprintf(out, "Hello, %s %s!", name, surname);
    fclose(out);
    return 0;
}
