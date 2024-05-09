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
#define SIZE 16

void input(int *arr);
void invprint(int *arr);

int main(void)
{
    int arr[SIZE];
    input(arr);
    invprint(arr);

    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

void invprint(int *arr)
{
    for(int i=0; i<SIZE; i++)
    {
        if((i<SIZE/4||SIZE/2 <= i) && i < 3*SIZE/4 )
        {
            int tmp,idx;
            tmp = arr[i];
            idx = i/(SIZE/2)*SIZE+SIZE/2-i-1;
            arr[i] = arr[idx];
            arr[idx] = tmp;
        }
        printf("%d ",arr[i]);
    }
}
