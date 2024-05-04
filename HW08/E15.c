/*
������������� � �������������
������� 10 ����� � ��������� �� -500 �� 500 � ��������� �� ���� ��������: � ���� �������� ������ �������������, �� ������ - ������ �������������.
�����, ������ ����, ������������. ������� �� ����� ��� �������� ����� ��������.
Input format
10 ����� ����� ����� ������.
Output format
������ ������������� �����, ����� ������������� �����, ����� ������.
*/
#include <stdio.h>
#define SIZE 10

void input(int* arr);
void print(int* arr, int n);
int findPlus(int* in, int* out);
int findMinus(int* in, int* out);


int main(void)
{
    int arr[SIZE] = {0}, Plus[SIZE] = {0}, Minus[SIZE] = {0}, Nminus = 0, Nplus = 0;
    input(arr);
    Nplus = findPlus(arr,Plus);
    Nminus = findMinus(arr,Minus);
    print(Plus,Nplus);
    print(Minus,Nminus);
    return 0;
}

void input(int* arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}
void print(int* arr, int n)
{
    for(int i=0; i< n; i++)
        printf("%d ", arr[i]);
}

int findPlus(int* in, int* out)
{
    int cnt = 0;
    for(int i = 0; i < SIZE; i++)
    {
        if(in[i]>0)
            out[cnt++] = in[i];
    }
    return cnt;
}

int findMinus(int* in, int* out)
{
    int cnt = 0;
    for(int i = 0; i < SIZE; i++)
    {
        if(in[i]<0)
            out[cnt++] = in[i];
    }
    return cnt;
}
