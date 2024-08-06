/*
 * Эксперименты с комбинаторикой и Ckn
 * */
#include <stdio.h>
#include <inttypes.h>

#define MAX_DIGITS 10

void cnt_dgt(const char *str, int *ht_map) {
    for (const char *p = str; *p; p++) {
        if (*p >= '0' && *p <= '9') {
            ht_map[*p - '0']++;
        }
    }
}

int32_t slct(int32_t n, int32_t k) {
    if (k > n) {
        return 0;
    }
    int32_t r = 1;
    for (int32_t d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

int cnt_3dgt_nums(const char *str) {
    int ht_map[MAX_DIGITS] = {0};
    int dgts[MAX_DIGITS];
    int dgt_cnt = 0;

    cnt_dgt(str, ht_map);
    for (int i = 0; i < MAX_DIGITS; i++) {
        if (ht_map[i] > 0) {
            dgts[dgt_cnt++] = i;
        }
    }

    if(dgt_cnt == 1) {
        return 1;
    }
    if(dgt_cnt == 2) {
        return 4;
    }

    return slct(dgt_cnt, 3);
}

int main(void) {
    char inp[1001];
    scanf("%100s", inp);
    printf("%d\n", cnt_3dgt_nums(inp));
    return 0;

}

