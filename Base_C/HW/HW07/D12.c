#include <stdio.h>
#include <inttypes.h>
/*
Дана монотонная последовательность, в которой каждое натуральное число k встречается ровно k раз:
1, 2, 2, 3, 3, 3, 4, 4, 4, 4,… Выведите первые n членов этой последовательности. Только один цикл for.
*/
int32_t r_row(int32_t n);

int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    r_row(n);
    return 0;
}
int32_t r_row(int32_t n)
{
    int32_t cnt=0;
    static int32_t nmax = 0;
    if(n>0)
    {
        if(nmax < n)
            nmax = n;
        cnt = r_row(n-1);
        for(int i=0; i<n && cnt < nmax; ++i,++cnt)
            printf("%"PRId32" ",n);
    }
    return cnt;
}
