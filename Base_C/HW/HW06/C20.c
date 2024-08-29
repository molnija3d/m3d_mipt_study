#include <stdio.h>
#include <inttypes.h>
/*
Скобки
Проверить строку состоящую из скобок "(" и ")" на корректность.
Input format
На вход подается строка состоящая из символов '(', ')' и заканчивающаяся символом '.'. Размер строки не более 1000 символов.
Output format
Необходимо напечатать слово YES если скобки расставлены верно и NO в противном случае.
 */

int32_t cnt_bracket(char c);


int main(void)
{
    char c;
    int32_t cnt;

    while((c=getchar())!='.')
        if((cnt=cnt_bracket(c))== -1)
        {
            printf("NO\n");
            return 0;
        }

    printf((cnt == 0)? "YES\n": "NO\n");
    return 0;
}


int32_t cnt_bracket(char c)
{
    static _Bool is_first = 1;
    static int32_t cnt=0;
    if((c == ')')&&(is_first == 1))
        return -1;

    if(c == '(')
    {
        cnt++;
        is_first = 0;
    }
    else if (c == ')')
    {
        cnt--;
        if (cnt == 0)
            is_first = 1;
    }

    return cnt;
}
