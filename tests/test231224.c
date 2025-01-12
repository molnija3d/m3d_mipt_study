#include <stdio.h>

void my_print(int arr[3][4]);
void fill_arr(int my_arr[3][4]);
void main(void) {
    int arr[3][4] = {0};
    my_print(arr);    
    printf("/n");
    fill_arr(arr);
    my_print(arr);
    
}

void fill_arr(int my_arr[3][4]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            my_arr[i][j] = i+j;
        }
    }
    my_print(my_arr);
}
void my_print(int arr[3][4]){
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", arr[i][j]);
        }
    }
}
