/*
Три раза
В файле input.txt дана строка. Вывести ее в файл output.txt три раза через запятую и показать количество символов в ней.
Input format
Строка из английских букв и пробелов. Не более 100 символов. В конце могут быть незначащие переносы строк.
Output format
Исходная строка 3 раза подряд, через запятую пробел и количество символов в ней.
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    
    char str[101] = {'\0'};
    fscanf(inp, "%[^EOF^\n]s", str);
    fclose(inp);
    fprintf(out, "%s, %s, %s %d", str, str, str, (int)strlen(str));
    fclose(out);
    return 0;
}
