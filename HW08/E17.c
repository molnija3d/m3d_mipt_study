/*
������ ���� ���
��� ������ �� 10 ���������. � ������� ����� ��������, ������� � ��� ����������� ������ ���� ���, � ������� �� �� �����.
Input format
10 ����� ����� ����� ������
Output format
�������� ������� ����������� ������ ���� ��� ����� ������
*/
#include <stdio.h>
#define SIZE 10

void input(int* arr);
void PrintRare(int* arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    PrintRare(arr);
    return 0;
}

void input(int* arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

void PrintRare(int* arr)
{
    for(int i = 0; i < SIZE; i++)
    {
        _Bool flag = 1;
        for(int j=0; j< SIZE; j++)
            if((i!=j) && arr[i] == arr[j])
                flag = 0;

        if(flag)
            printf("%d ",arr[i]);
    }
}
