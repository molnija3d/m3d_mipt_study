#include <stdio.h>
#include <time.h>
double DELAY = 3;
int main()
{ 
  int i = 0;
  clock_t begin = clock();
  printf("%ld\n", clock() - begin);
  while(i++ < 10000);
  printf("%ld\n", clock() - begin);
  
  while((double)(clock() - begin)/CLOCKS_PER_SEC < DELAY)
  {
         //printf("%ld\n",clock()); 
  }
  printf("Hello World %ld\n",CLOCKS_PER_SEC);
  return 0;
}
