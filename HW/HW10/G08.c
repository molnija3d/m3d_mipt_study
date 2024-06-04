/*
Числа в массив
В файле input.txt дана строка, не более 1000 символов, содержащая буквы, целые числа и иные символы.
Требуется все числа, которые встречаются в строке, поместить в отдельный целочисленный массив.
Например, если дана строка "data 48 call 9 read13 blank0a", то в массиве числа 48, 9, 13 и 0. Вывести массив по возрастанию в файл output.txt.
Input format
Строка из английских букв, цифр и знаков препинания
Output format
Последовательность целых чисел отсортированная по возрастанию
 */
#include <stdio.h>

int strinp(FILE *inp,char* str);
int find_digits(FILE *fl, int *arr);
void sort_array(int size, int* a);
void print_digits(FILE *outp,int n,int *arr);

int main(void)
{
    enum {str_len = 500}; //if we have 1000 symbols int the string, than there is no morw than 500 numbers separated by only one symbol 
    FILE *inp = fopen("input.txt","r");
    FILE *outp = fopen("output.txt","w");

    int arr[str_len]= {0}, 
        n = 0;

    n = find_digits(inp,arr);
    sort_array(n,arr);
    print_digits(outp,n,arr);

    fclose(inp);
    fclose(outp);

    return 0;
}

int find_digits(FILE *fl, int *arr)
{
    int i = 0;
    char c = 0, 
         prev = 'a';  //any not a number
         
    while((c = fgetc(fl)) != EOF)
    {
        if(c>= '0' && c <= '9')
        {
            arr[i] *= 10;
            arr[i] += c - 0x30;
        }
        else if(prev >='0' && prev <= '9')
        {
            i++;
        }
        prev = c;
    }
    return i;

}
void print_digits(FILE *outp,int n,int *arr)
{
    for(int i=0; i < n; i++)
    {
        fprintf(outp, "%d ", arr[i]);
    }
}

void sort_array(int size, int* a)    //shell-sort
{
    for (int stp = size / 2; stp > 0; stp /= 2)
    {
        for (int i = stp; i < size; i++)
        {
            int j = i;
            int temp = a[j]; //remember number at postition stp

            while( j-stp >= 0 && a[j-stp] > temp)   //if val at position j-stp > temp, change val at j with val at j-stp
            {
                a[j] = a[j-stp];
                j -= stp;
            }
            a[j] = temp; //place data[i] at new position.
        }
    }
}

int strinp(FILE *inp,char* str)
{
    int res = 0;
    res = fscanf(inp, "%[a-zA-Z0-9 ,.;:!?-\'\")(]s", str);
    
    return res;
}
