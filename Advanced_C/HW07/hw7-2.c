/*
 Задача 7-2-Вид сверху
 В программе описана структура для хранения двоичного дерева:
 typedef struct tree {
     datatype key;
         struct tree *left, *right;

 } tree;
Необходимо реализовать функцию, которая печатает вид дерева сверху. Функция должна строго соответствовать прототипу: void btUpView(tree *root)
В качестве ответа загрузите только одну функцию void btUpView(tree *root)
Пример №1
Данные на входе:

       10
     /   \
   5     15
  / \   /  \
 3   7 13   18
/   /
1   6

*/
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef int32_t datatype;
typedef struct tree {
    datatype key;
    struct tree *left, *right;

} tree;

void insert_t(tree **root, datatype key);
void go_left(tree *root);
void go_right(tree *root);
void btUpView(tree *root);

int main() {
    tree *my_tree = NULL;
    insert_t(&my_tree, 10);
    insert_t(&my_tree, 5);
    insert_t(&my_tree, 15);
    insert_t(&my_tree, 3);
    insert_t(&my_tree, 7);
    insert_t(&my_tree, 13);
    insert_t(&my_tree, 18);
    insert_t(&my_tree, 1);
    insert_t(&my_tree, 6);
    btUpView(my_tree);
}

void btUpView(tree *root) {
    go_left(root);
    if(root->right) {
        go_right(root->right);
    }
    printf("\n");
}

void go_left(tree *root) {
    if(root->left) {
        go_left(root->left);
    }
    printf("%d ", root->key);
}

void go_right(tree *root) {
    printf("%d ", root->key);
    if(root->right) {
        go_left(root->right);
    }
}

void insert_t(tree **root, datatype key) {
    if(!*root) {
        *root = (tree *) calloc(1, sizeof(tree));
        (*root)->key = key;
    }
    else if((*root)->key < key) {
        insert_t(&(*root)->right, key);
    }
    else {
        insert_t(&(*root)->left, key);
    }
}
