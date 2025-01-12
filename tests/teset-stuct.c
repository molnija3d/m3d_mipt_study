#include <stdio.h>
#include <string.h>

typedef struct { /* шаблон структуры: дескриптором является book */
    char title [41] ;
    char author [31] ;
    float value;
} book;

int main() {
    book my_book = {.value = 18.9, .author = "txt", 0.25};
    return 0;
}
