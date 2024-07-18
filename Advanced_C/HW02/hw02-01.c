#include <stdio.h>
#include <inttypes.h>

typedef struct list
{
        void *address;
        size_t size;
        char comment[64];
        struct list *next;
} list;

void *findMaxBlock(list *head);

int main()
{

        return 0;
}
