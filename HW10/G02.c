/*
Строка и цифры
Считать число N из файла input.txt. Сформировать строку из N символов. N четное число, не превосходящее 26.
На четных позициях должны находится четные цифры в порядке возрастания, кроме 0, на нечетных позициях - заглавные буквы в порядке следования в английском алфавите.
Результат записать в файл output.txt
Input format
Четное N <= 26
Output format
Строка из английских букв и цифр
 */
#include <stdio.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");

    char str[27]= {'\0'};
    int num=0, cnt_num = 2,cnt_lett = 1;
    fscanf(inp,"%d",&num);
    fclose(inp);
    for(int i = 0; i < num; i++)
    {
        if(i % 2)
        {
            str[i] = 0x30 + cnt_num;
            cnt_num += 2;
            if(cnt_num > 9)
            {
                cnt_num = 2;
            }
        }
        else
        {
            str[i] = 0x40 + cnt_lett++;
            if(cnt_lett > 26)
             cnt_lett = 1;
        }
    }
    fprintf(out,"%s",str);
    fclose(out);
    return 0;
}
