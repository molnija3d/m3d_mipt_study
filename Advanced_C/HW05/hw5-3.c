/*
Задача 5-3-Польская запись
Формат ввода:
Строка состоящая из целых чисел и символов '+', '-', '*', '/', ' '. В конце строки символ '.'. Строка корректная. 
Длина строки не превосходит 1000 символов. Все числа и операции разделены ровно одним пробелом.
Формат вывода:
Целое число, результат вычисления выражения.
*/
#include <stdio.h>
#include <inttypes.h>
#define MAX_STACK 255

typedef int32_t datatype;
int32_t pst = 0;

datatype stack[MAX_STACK];
datatype pop();
void push(datatype val);
void operate(char c);
_Bool is_digit(char c);
_Bool is_operator(char c);
_Bool is_empty();
_Bool check_pst();
int32_t inp_str(char str[]);
int32_t calc_polska(char str[], int32_t len);

int32_t main() {
    char str[1001] = {0};
    int32_t len = 0;
    len = inp_str(str);
    printf("%"PRId32"\n", calc_polska(str, len));
    return 0;
}

int32_t inp_str(char str[]) {
    int32_t len= 0;
    char c = 0;
    while((c = getchar()) != '.') {
        str[len++] = c;
    }
    return len;
}

int32_t calc_polska(char str[], int32_t len) {
    for(int32_t i = 0; i < len; i++) {
        if(is_digit(str[i])) {
            datatype num = 0;
            for(num = 0; is_digit(str[i]); i++)
            {
                num *= 10;
                num += str[i] - '0';
            }
            push(num);
        }
        else {
            if(is_operator(str[i])) {
                operate(str[i]);
            }
        }
    }
    return pop();
}

void operate(char c) {
    datatype arg1 = pop(), arg2 = pop();
    switch(c) {
    case '+':
        push(arg1 + arg2);
        break;
    case '-':
        push(arg2 - arg1);
        break;
    case '*':
        push(arg1 * arg2);
        break;
    case '/':
        push(arg2/arg1);
        break;
    }
}

void push(datatype val) {
    stack[pst++] = val;
}

datatype pop() {
    datatype val = 0;
    if (check_pst()) {
        val = stack[--pst];
    }

    return val;
}

_Bool check_pst() {
    _Bool check = 1;
    if(pst < 0) {
        printf("Stack underflow ERROR");
        check = 0;
    }
    else if (pst > MAX_STACK) {
        printf("Stack overflow ERROR");
        check = 0;
    }
    return check;
}

_Bool is_digit(char c) {
    return ((c >= '0') && (c <= '9'));
}

_Bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

_Bool is_empty() {
    return (pst <= 0);
}
