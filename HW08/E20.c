/*
����������� �����
����������� ����� � ����� ���, ��� �� ���������� ������������ �����.
Input format
���� ����� �� ������������� �����
Output format
����� �� ������������� �����
*/

#include <stdio.h>

int makeItMax(int num);

int main(void)
{
    int num;
    scanf("%d",&num);
    printf("%d ",makeItMax(num));
    return 0;
}

int makeItMax(int num)
{
   int arr[11] = {0}, tmp, cnt = 0, max = 0; 
   
   do
   {
     arr[cnt++] = num%10;
   }
   while(num/=10);

   for(int i = 0; i < cnt; i++)
    {
      for(int j = i; j < cnt; j++)
      {
       if(arr[i] < arr[j])
           {
             tmp = arr[i];
             arr[i] = arr[j];
             arr[j] = tmp;
           }
      }
    }
    
    for(int i = 0; i < cnt; i++)
     max = max*10 + arr[i];
       
  return max;
}
