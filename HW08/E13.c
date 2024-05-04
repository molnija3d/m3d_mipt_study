/*
¬тора€ с конца ноль
—читать массив из 10 элементов и отобрать в другой массив все числа, у которых втора€ с конца цифра (число дес€тков) Ц ноль.
Input format
10 целых чисел через пробел.
Output format
÷елые числа через пробел, у котороых втора€ с конца цифра - ноль
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void print(int *arr, int n);
int findEven2(int *arr, int *res);


int main(void)
{
    int arr[SIZE] = {0}, res[SIZE] = {0}, n = 0;
    input(arr);
    n = findEven2(arr,res);
    print(res,n);
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}
void print(int *arr, int n)
{
    for(int i=0; i< n; i++)
        printf("%d ", arr[i]);
}

int findEven2(int *arr, int *res)

{
    int cnt = 0;;
    for(int i = 0; i <SIZE; i++)
    {
        if((arr[i]/10)%10 == 0)   //(arr[i] > 99) && -чтобы исключить 1,2,3,4 и т.д.
          res[cnt++] = arr[i];
    }
  
    return cnt;
}

