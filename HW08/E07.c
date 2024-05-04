/*
�������� ���������
������� ������ �� 10 ��������� � ��������� �������� �������� ��� 1-�� � 2-�� ������� �������.
���������� �������� ��������� ������ � ���������� ��� ����� ������.
Input format
10 ����� ��������� ������� ����� ������.
Output format
10 ����� ��������� ������� ����� ������.
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void print(int *arr);
void inverse(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    inverse(arr);
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
void inverse(int *arr)
{
    int tmp[SIZE]= {0},
        hSizeBtm = SIZE/2,
        hSizeTop = SIZE;

    for(int i=0; i<hSizeBtm; i++)
        tmp[i] = arr[hSizeBtm - 1 - i];

    for(int i=hSizeBtm; i<hSizeTop; i++)
        tmp[i] = arr[hSizeTop + hSizeBtm - 1 - i];

    for(int i=0; i<SIZE; i++)
        arr[i] = tmp[i];

}
