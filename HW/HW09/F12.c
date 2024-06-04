/*
Поменять местами
Составить функцию которая меняет в массиве минимальный и максимальный элемент местами. 
Прототип функции void change_max_min(int size, int a[])
Input format
Функция принимает на вход размер массива и массив чисел типа int
Output format
Функция не возвращает значения, измененный массив сохраняется на месте исходного.
*/

void change_max_min(int size, int a[])
{
    int min=a[0], max=a[0], minpos=0, maxpos=0;
    for(int i=0; i < size; i++)
    {
      if(max < a[i])
      {
        max = a[i];
        maxpos = i;
      }
      if(min > a[i])
      {
        min = a[i];
        minpos = i;
      }
  }
    a[minpos] = max;
    a[maxpos] = min;
}