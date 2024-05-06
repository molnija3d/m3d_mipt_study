/*
��� ������ �� 10 ���������. ����������, ����� ����� � ������� ����������� ���� �����. �������������, ��� ����� ����� ����� 1.
*/
#include <stdio.h>
#define SIZE 10

void input(int* arr);
int fPopular(int* arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    printf("%d",fPopular(arr));
    return 0;
}

void input(int* arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

int fPopular(int* arr)
{
    int frqncy[150] = {0}, mxIdx = arr[0];  
    
    for (int i = 0; i < SIZE; i++)
    {
        frqncy[arr[i]]++;    // �������� ������ ��� ������������� ����� ������ 149. �� ������������� � ������� ��� 149 - ����� �� ������� �������
        
        if (frqncy[arr[i]] > frqncy[mxIdx])
        {
            mxIdx = arr[i]; 
        }
    }
    return mxIdx; 
}
