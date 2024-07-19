#include <stdio.h>
#include <time.h>
int main(void)
{
        time_t mytime = time(NULL);
        struct tm *now = localtime(&mytime);
        printf("Date: %d.%d.%d\n", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
        printf("Time: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);
        return 0;
        
}
