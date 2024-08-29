/*
Заменить a на b
В файле input.txt дана символьная строка не более 1000 символов.
Необходимо заменить все буквы "а" на буквы "b" и наоборот, как заглавные, так и строчные.
Результат записать в output.txt.
Input format
Строка из маленьких и больших английских букв, знаков препинания и пробелов.
Output format
Строка из маленьких и больших английских букв, знаков препинания и пробелов.
 */
#include <stdio.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN = 1001};
    char str[STRLEN] = {'\0'};

    fscanf(inp,"%[a-zA-Z ]s", str);
    fclose(inp);

    for(int i = 0; i < STRLEN && str[i] != '\0'; i++)
    {
        switch(str[i])
        {
            case 'a':
             str[i] = 'b';
             break;
            case 'b':
             str[i] = 'a';
             break;
            case 'A':
             str[i] = 'B';
             break;
            case 'B':
             str[i] = 'A';
             break;
        }
    }
    fprintf(out, "%s", str);
    fclose(out);
    return 0;
}
