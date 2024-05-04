/*
����������� ����� ������� ������
������� ������ �� 10 ��������� � ��������� ����������� ����� ������ �� 1.
Input format
10 ����� ����� ����� ������
Output format
10 ����� ����� ����� ������ ��������� ������ �� 1 ������� ����������
*/
#include <stdio.h>
#define SIZE 12

void input(int *arr);
void print(int *arr);
void Rroll(int *arr, int cnt);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    Rroll(arr,4);
    print(arr);
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}
void print(int *arr)
{
    for(int i=0; i< SIZE; i++)
        printf("%d ", arr[i]);
}
void Rroll(int *arr, int cnt)
{
    int tmp[SIZE]={0};
    for(int i = 0 ; i < SIZE; i++)
    {
      if(i+cnt < SIZE)
       tmp[i+cnt] = arr[i];
      else
       tmp[i+cnt-SIZE] = arr[i];
    }
    
    for(int i = 0 ; i < SIZE; i++)
       arr[i] = tmp[i];
    
}
