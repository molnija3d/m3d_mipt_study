/*
Сортировка по взрастанию
Написать только одну функцию, которая сортирует массив по возрастанию. Необходимо реализовать только одну функцию, всю программу составлять не надо.
Строго согласно прототипу. Имя функции и все аргументы должны быть: void sort_array(int size, int a[]).
Всю программу загружать не надо, только одну эту функцию. Можно просто закомментировать текст всей программы, кроме данной функции.
Input format
Функция принимает на вход, первый аргумент - размер массива, второй аргумент - адрес нулевого элемента.
Output format
Функция ничего не возвращает. Производит сортировку переданного ей массива по возрастанию.
*/


void sort_array(int size, int a[])    //shell-sort
{
    for (int stp = size / 2; stp > 0; stp /= 2)
    {
        for (int i = stp; i < size; i++)
        {
            int j=i;
            int temp = a[j]; //remember number at postition stp
            

            while( j-stp >= 0 && a[j-stp] > temp)   //if val at position j-stp > temp, change val at j with val at j-stp
            {
                a[j] = a[j-stp];
                j -= stp;
            }
           a[j] = temp; //place data[i] at new position.
        }
    }
}
