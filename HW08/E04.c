/*
��� ���������
������� ������ �� 10 ��������� � ����� � ��� ��� ������������ �������� � ���������� �� �����.
Input format
10 ����� ����� ����� ������.
Output format
����� ���� ������������ ���������
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void twoMax(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    twoMax(arr);
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

void twoMax(int *arr)
{
    int max1=arr[0], max2=-arr[0];
    
    for(int i=1; i<SIZE; i++)
    {
        if(max1 < arr[i])
        {   
            max2 = max1;
            max1 = arr[i];
        }
        else if (max2 < arr[i])
            max2 = arr[i];
    }
    printf("%d\n", max1 + max2);
}
