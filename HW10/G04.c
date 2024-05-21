/*
По одному разу
В файле input.txt даны два слова не более 100 символов каждое, разделенные одним пробелом.
Найдите только те символы слов, которые встречаются в обоих словах только один раз.
Напечатайте их через пробел в файл output.txt в лексикографическом порядке.
Input format
Два слова из маленьких английских букв через пробел. Длинна каждого слова не больше 100 символов.
Output format
Маленькие английские буквы через пробел.
 */
#include <stdio.h>

int main(void)
{
    FILE *inp = fopen("input.txt","r");
    FILE *out = fopen("output.txt","w");
    enum {STRLEN=101};
    char word_1[STRLEN]= {'\0'};
    char word_2[STRLEN]= {'\0'};
    int idx_1_max=0,idx_2_max=0,cnt=0;

    fscanf(inp,"%s%s",word_1, word_2);
    fclose(inp);

    for(int i = 0; i < STRLEN && word_1[i]!= '\0'; idx_1_max = 1 + i++);
    for(int i = 0; i < STRLEN && word_2[i]!= '\0'; idx_2_max = 1 + i++);

    for(int idx_1 = 0; idx_1 < idx_1_max; idx_1++)
    {
        cnt=0;
        for (int idx_12 = 0; idx_12 < idx_1_max && cnt < 3; idx_12++)
        {
            if(word_1[idx_1] == word_1[idx_12])
            {
                cnt++;
            }
        }

        if(cnt == 2)  //if there are two equal letters in the first word - break
        {
            cnt = 3; 
        }
        
        for (int idx_2 = 0; idx_2 < idx_2_max && cnt < 3; idx_2++)
        {
            if(word_1[idx_1] == word_2[idx_2])
            {
                cnt++;
            }
        }

        if(cnt == 2) //if there are two equal letters in both words - output a letter
        {
            fprintf(out,"%c ",word_1[idx_1]);
        }
    }

    fclose(out);
    return 0;
}
