#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#define LEN 200

void kmp(char str[], int32_t p[], int32_t n);
void kmp2(char str[], int32_t p[], int32_t n);
void print_p(int32_t p[], int32_t n);


int main() {
    char str[LEN] = {0}, fnd[LEN] = {0}, res[LEN + LEN + 1] = {0};
    int32_t p[LEN + LEN + 1] = {0}, n = 0;
    scanf("%s",str);
    scanf("%s", fnd);
    n = strlen(str);
    kmp(str, p, n);
    print_p(p, n + 1);

    sprintf(res,"%s#%s", fnd, str);
    printf("%s\n", res);
    n = strlen(res);
    kmp(res, p, n);
    print_p(p, n + 1);
    return 0;
}

void print_p(int32_t p[], int32_t n) {
    for (int32_t i = 0; i < n; i++) {
        printf("% "PRId32, p[i]);
    }
    printf("\n");
}

void kmp(char str[], int32_t p[], int32_t n) {
    int32_t k = 0;
    p[0] = -1;
    for(int32_t i = 1; i < n + 1; i++) {
        k = p[i - 1];
        while (k > -1 && str[k] != str[i - 1]) {
            k = p[k];
        }
        p[i] = k + 1;
    }

}

void kmp2(char str[], int32_t p[], int32_t n) {
    int32_t k = 0;
    p[0] = 0;
    for(int32_t i = 1; i < n; i++) {
        k = p[i - 1];
        while (k > 0 && str[k] != str[i])	   {
            k = p[k - 1];
        }
        if(str[k] == str[i]) {
            k++;
        }
        p[i] = k;
    }

}
