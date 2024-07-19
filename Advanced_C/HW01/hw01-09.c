#include <stdio.h>
#include <inttypes.h>
#define CNT 4

int8_t fnd_cnt(int32_t p, int32_t W[CNT]);

int main()
{
    int32_t p = 0;
    int8_t cnt = 0;
    int32_t W[CNT] = {1, 3, 9, 27};
    scanf("%" SCNd32, &p);
    cnt = fnd_cnt(p,W);
    printf("%d\n", cnt);
    return 0;
}

int8_t fnd_cnt(int32_t p, int32_t W[CNT])
{
    int8_t s[CNT] = {0};
    int32_t w = 0, res = 0;

    for(int8_t m = -1; m < 2 && res == 0; m++)
        for(int8_t j = -1; j < 2 && res == 0; j++)
            for(int8_t k = -1; k < 2 && res == 0; k++)
                for(int8_t l = 0; l < 2 && res == 0; l++)
                {
                    w = 0;
                    s[0] = m;
                    s[1] = j;
                    s[2] = k;
                    s[3] = l;

                    for(int8_t i = 0; i < CNT; i++)
                    {
                        w += s[i] * W[i];
                    }
                    if( p == w )
                    {
                        res = w;
                    }
                }

    if ( !res )
    {
        res = -1;
    }
    else
    {
        res = 0;
        for(int8_t i = 0; i < CNT; i++)
        {
            if(s[i] != 0)
            {
                res++;
            }
        }
    }
    return res;
}
