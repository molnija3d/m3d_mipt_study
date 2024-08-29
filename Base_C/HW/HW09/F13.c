/*
В заданном интервале
Составить функцию которая возвращает количество элементов на заданном отрезке [from, to] для массива.
Прототип функции int count_between(int from, int to, int size, int a[])
Например, на отрезке [4, 6] в массиве 1 2 3 4 5 6 7 8 9 10 функция вернет 3 значения
Input format
Функция принимает значения концов отрезка from и to, размер массива, массив целых чисел.
Output format
Функция возвращает целое число - количество числе в интервале [from, to]
*/

int count_between(int from, int to, int size, int a[])
{
    int cnt=0;
    for(int i=0; i< size; i++)
    {
        if(a[i]>=from && a[i]<=to)
            cnt++;
    }
    return cnt;
}

