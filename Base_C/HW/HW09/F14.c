/*
Сумма в интервале
Составить функцию которая возвращает сумму элементов в заданном отрезке [from, to] для массива. 
Прототип функции int sum_between_ab(int from, int to, int size, int a[])
Input format
Функция принимает концы отрезка from и to, размер массива, массив целых чисел
Output format
Функция возвращает сумму элементов в интервале [from, to]
*/

int sum_between_ab(int from, int to, int size, int a[])
{ 
  int sum=0;
  int A=from,B=to;
  if(A>B)
   A=to,B=from;
   
  for(int i=0; i< size;i++)
  {
    if(a[i]>=A && a[i]<=B)
     sum+=a[i];
  }
  return sum;
}

