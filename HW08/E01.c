/* 
������� �������������� �����
������ c ���������� ������ �� 5 ���������, ����� ������� �������������� ���� ��������� �������.
Input format
5 ����� �� ������� ����� ����� ������
Output format
���� ����� � ������� "%.3f"
*/
#include <stdio.h>
#define SIZE 5

void input(int *arr);
float average(int *arr);

int main(void)
{
  int arr[SIZE] = {0};
  input(arr);
  printf("%.3f\n",average(arr));
  return 0;
}

void input(int *arr)
{
    for(int i=0;i<SIZE;i++)
          scanf("%d",arr+i);
}

float average(int *arr)
{
    int avrg = 0;
    for(int i=0;i<SIZE;i++)
        avrg +=arr[i];
    return (float) avrg/SIZE;
}
