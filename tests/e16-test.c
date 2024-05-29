#include <stdio.h>

int Input(int* arr, int n);

int MAX_NUM(int *arr, int len);

int Is_Exsist(int* arr, int num, int len);

int most_often(int* in, int* couted_num, int* counter, int n);


int main(void)
{
enum {SIZE = 10};
int in[SIZE] = {4,1,2,1,11,2,34,11,0,11};
int counted_num[SIZE]={0};
int counter[SIZE]={0};
//Input(in, SIZE);
most_often(in, counted_num, counter, SIZE);
printf("%d\n", counted_num[MAX_NUM(counter, SIZE)]);

return 0;

}


int MAX_NUM(int *arr, int len)
{
    int max = 0;
    int max_i = 0;
    for (int i=0; i<len; i++)
    {
        if (arr[i] >  max)
        {
            max = arr[i];
            max_i = i;
        }
    }
    return max_i;
}

int Input(int* arr, int n)
    {
        int i;
        for (i=0; i<n; i++)
        {
         scanf("%d", &arr[i]); 
        }
        return i;
    }

int Is_Exsist(int* arr, int num, int len)
{

    for (int i=0; i<len; i++)
    {
    if (num == arr[i])
        {
            return i;
        }
    }
    return -1;
}

int most_often(int* in, int* counted_num, int* counter, int n)
{

    int count = 0;
    if (counter[count] == 0)
        count++;
    for (int i = 0; i<n; i++)
        {
            if (Is_Exsist(counted_num, in[i], n) != -1)
                {
                    counter[Is_Exsist(counted_num, in[i], n)]++;
                }
            counted_num[count] = in[i];
            counter[count] = 1;
            count++;
        }

    return 0;
}