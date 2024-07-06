

#include <stdio.h>
#define STR_SIZE 100

int main()
{
    char st[STR_SIZE] = "hello";
    printf("%llu\n", sizeof(st) / sizeof(st[0])); // размер массива
    char c;
    int i = 0;
    c = getchar();
    while (c != '\n' && c != '0' && i < STR_SIZE - 1 )
    { 
        st[i++] = c;
        c = getchar();
    } 
    
    c == '0' ? st[--i] = 0 : st[i] = 0;

    printf("\n%s\n", st);

    for (i = 0; st[i] != 0; i++)
        putchar(st[i]);

    return 0;
}
