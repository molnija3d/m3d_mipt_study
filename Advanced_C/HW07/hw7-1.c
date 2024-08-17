/*
Дана строка, состоящая из английских букв и пробелов. В конце строки символ точка. Все слова разделены одним пробелом.
Необходимо составить из слов односвязный список и упорядочить по алфавиту. Список необходимо удалить в конце программы.
Для сравнение строк можно использовать strcmp. Необходимо использовать данную структуры организации списка.
struct list {
	   char word[20];
	      struct list *next;

}


Необходимо реализовать односвязный список и обслуживающие его функции. add_to_list swap_elements print_list delete_list
Форма ввода:
Строка из английских символов 'a'-'z' и пробелов. В конце строки символ '.'. Длинна строки не более 1000 символов.
Формат вывода:
Упорядоченные по алфавиту слова.

Пример №1
Данные на входе:		efg abcd zzz.
Данные на выходе:	abcd efg zzz
Пример №2
Данные на входе:		fffff kkkkkk a.
Данные на выходе:	a fffff kkkkkk
*/
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

struct list {
    char word[20];
    struct list *next;

};

void add_to_list(struct list **lst, char str[]);
struct list *swap_elements(struct list *lst1, struct list *lst2);
void sort_list(struct list **lst);
void print_list(struct list *lst);
void delete_list(struct list *lst);
char my_strcmp(const char *a, const char *b);

int main() {
    struct list *lst = calloc(1, sizeof(struct list));
    char c, str[20] = {0};
    int8_t i = 0;
    lst->word[0] = 0;

    while( (c = getchar()) != '.' ) {
        if(c == ' ') {
            if(i > 0) {
                str[i] = '\0';
                add_to_list(&lst->next, str);
                i = 0;
            }
        }
        else {
            str[i++] = c;
        }
    }
    str[i] = 0;

    add_to_list(&lst, str);

    sort_list(&lst);
    print_list(lst);

    delete_list(lst);
    return 0;
}

void add_to_list(struct list **lst, char str[]) {
    if(!*lst) {
        struct list *new = calloc(1, sizeof(struct list));
        sprintf(new->word,"%s",str);
        *lst = new;
    }
    else {
        add_to_list(&(*lst)->next, str);
    }
}

void delete_list(struct list *lst) {
   if(lst->next) {
        delete_list(lst->next);
    }
    free(lst);
}


void sort_list(struct list **lst) {
    struct list *tmp;
    bool unsorted = true;
    while(unsorted) {
        tmp = *lst;
        unsorted = false;
        while(tmp->next) {
            if(tmp->next->next && my_strcmp(tmp->next->word, tmp->next->next->word) > 0) {
                tmp->next = swap_elements(tmp->next, tmp->next->next);
                unsorted = true;
            }
            tmp = tmp-> next;
        }
    }
}

struct list *swap_elements(struct list *lst1, struct list *lst2) {
    lst1->next = lst2->next;
    lst2->next = lst1;
    return lst2;
}

void print_list(struct list *lst) {
    if(lst->word[0]) {
        printf("%s ", lst->word);
    }

    if(lst->next) {
        print_list(lst->next);
    }
    else {
        printf("\n");
    }
}

char my_strcmp(const char *a, const char *b)
{
    while (*a && *b && *a == *b)
    {
        a++;
        b++;

    }
    return *a - *b;

}

