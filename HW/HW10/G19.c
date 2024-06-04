/*
Составить палиндром
Разработать функцию дана строка из маленьких английских букв. Составить из символов палиндром максимальной длинны.
При составлении палиндрома буквы в палиндроме должны быть расположены в лексикографическом порядке. Записать ответ в файл output.txt.
Input format
Строка из маленьких английских букв. Не более 1000 символов.
Output format
Строка из маленьких английских букв.
 */
#include <stdio.h>

int strinp(FILE *inp, char* str);
void sort_str(int size, char* a);
void make_palindrom(int in_len, char *in_str, char *plndr);

int main(void)
{
    enum {str_len = 1001};
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");
    char in_str[str_len]= {'\0'};
    char palindrom[str_len] = {'\0'};
    int len = 0;
    len = strinp(inp, in_str);
    sort_str(len, in_str);
    make_palindrom(len, in_str, palindrom);

    fprintf(outp, "%s", palindrom);

    fclose(inp);
    fclose(outp);

    return 0;
}
void make_palindrom(int in_len, char *in_str, char *plndr)
{
    int e_idx = 0, s_idx = 0;
    char spare[33] = {'\0'};
    char even[1001] = {'\0'};
    for(int i = 1; i <= in_len; i++)
    {
        if(in_str[i-1] == in_str[i])
        {
            even[e_idx++] = in_str[i-1];
            even[e_idx++] = in_str[i++];
        }
        else
        {
            spare[s_idx++] = in_str[i-1];
        }
    }

    int lft_idx = e_idx + 1 * (s_idx > 0);
    char left[lft_idx];
    _Bool flag = 1;
    int pldr_lidx = 0;
    
    for(int i = 0; i < lft_idx && flag; i++)
    {
        if((i+i) < e_idx)
        {
            left[i] = even[i+i];
            pldr_lidx = i;
        }
        else if (s_idx > 0)
        {
            left[i] = spare[0];
            flag = 0;
            pldr_lidx = i + 1;
        }
    }

    if(pldr_lidx % 2 != 0)
    {
        for(int i = 0; i < pldr_lidx - 1; i++)
        {
            plndr[i] = left[i];
            plndr[2 * pldr_lidx - 2 - i] = plndr[i];
        }
        plndr[pldr_lidx - 1] = left[pldr_lidx - 1];
    }
    else
    {
        for(int i = 0; i < pldr_lidx; i++)
        {
            plndr[i] = left[i];
            plndr[2 * pldr_lidx - 2 - i] = plndr[i];
        }
    }
    plndr[2 * pldr_lidx - 1] = '\0';
}


int strinp(FILE *inp, char* str)
{
    int i = 0;
    char c = 0;
    while((c = fgetc(inp)) != EOF)
    {
        if((c >= 'a' && c <= 'z')) //in auto test there are only small letters
        {
            str[i++] = c;
        }
    }
    str[i] = '\0';
    return i;
}

void sort_str(int size, char* a)    //shell-sort
{
    for (int stp = size / 2; stp > 0; stp /= 2)
    {
        for (int i = stp; i < size; i++)
        {
            int j = i;
            int temp = a[j]; //remember number at postition stp

            while( j - stp >= 0 && a[j - stp] > temp)   //if val at position j-stp > temp, change val at j with val at j-stp
            {
                a[j] = a[j - stp];
                j -= stp;
            }
            a[j] = temp; //place data[i] at new position.
        }
    }
}
