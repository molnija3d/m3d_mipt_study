#include <stdio.h> 
#include <unistd.h>
 
void input(int* num1, int* num2); 
 
int main(int argc, char **argv) 
{ 
    int num1 = 0, num2 = 0; 
    input(&num1, &num2); 
    int d = 0;
    while(d = getopt(argc,argv,"f:") != 'f');
    printf("%d %s\n", d, optarg);
    printf ("main module:\n"); 
    printf ("num1 = %d, num2 = %d\n", num1, num2); // здесь какая-то ерунда 
} 
 
void input(int* nm1, int* nm2) { 
    char data[3];   
    int i = 0xAAAA;
    printf("i = %#X\n", i); 
    scanf("%s", data);
    printf("i = %#X\n",i); 
    *nm1 = data[0] - 'A' + 1; 
    *nm2 = data[1] - '0'; 
    printf ("input module:\n"); 
    printf ("num1 = %d, num2 = %d\n", *nm1, *nm2); // здесь всё верно 
    printf ("----------\n"); 
}