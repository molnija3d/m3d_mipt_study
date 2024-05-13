/*
���������� �� ����������
�������� ������ ���� �������, ������� ��������� ������ �� �����������. ���������� ����������� ������ ���� �������, ��� ��������� ���������� �� ����.
������ �������� ���������. ��� ������� � ��� ��������� ������ ����: void sort_array(int size, int a[]).
��� ��������� ��������� �� ����, ������ ���� ��� �������. ����� ������ ���������������� ����� ���� ���������, ����� ������ �������.
Input format
������� ��������� �� ����, ������ �������� - ������ �������, ������ �������� - ����� �������� ��������.
Output format
������� ������ �� ����������. ���������� ���������� ����������� �� ������� �� �����������.
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
