#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
typedef struct node
{
    struct node *left;
    struct node *right;
    int data;
} node;

void push_to_tree(node **, int);
void print_to_tree(node *, int);
void rand_tree(node **, int);
void check(int *);
void print();


int main() {
    node *tree = NULL;
    int n = 0,
        count = 0;
    // while(1) {
    //     print();
    //     check(&count);
    //     switch (count) {
    //         case 1:
    //             check(&n);
    //             push_to_tree(&tree, n);
    //             break;
    //         case 2:
    //             check(&n);
    //             rand_tree(&tree, n);
    //             break;
    //         case 3:
    //             print_to_tree(tree, 0);
    //             break;
    //         default:
    //         break;
    //     }
    //     if (count == 6) {
    //         break;
    //     }
    // }
    // check(&n);
    // rand_tree(&tree, n);
    // node *tree = (node *)malloc(sizeof(node));
    push_to_tree(&tree, 5);
    push_to_tree(&tree, 6);
    push_to_tree(&tree, 4);
    push_to_tree(&tree, 7);
    push_to_tree(&tree, 3);
    push_to_tree(&tree, 8);
    push_to_tree(&tree, 2);
    push_to_tree(&tree, 9);
    push_to_tree(&tree, -1);
    push_to_tree(&tree, 1);
    print_to_tree(tree, 0);
    return 0;
}

void push_to_tree(node **tree, int data)
{
    node *tmp = (node *)malloc(sizeof(node));
    if (*tree == NULL) {
        tmp->data = data;
        tmp->left = NULL;
        tmp->right = NULL;
        *tree = tmp;
        return;
    } else {
        // tmp->data = data;
        // tmp->right = NULL;
        // tmp->left = NULL;
        if (data >= (*tree)->data) {
            // printf("ITS push right\n");
            push_to_tree((&(*tree)->right), data);
        }
        else {
            // printf("ITS push left\n");
            push_to_tree((&(*tree)->left), data);
        }
    }
}

void print_to_tree(node *tree, int level) {
    if (tree == NULL) {
        // printf("ITS NULL\n");
        return;
    }

    print_to_tree(tree->right,level+1);
    for (int i = 0; i <= 2 * level; i++)
        printf(" ");
    printf("%d\n",tree->data);
    print_to_tree(tree->left,level+1);

}
void rand_tree(node **tree, int n) {
    srand(time(NULL));
    int rand1 = n;
    for (int i = 0; i < n; i++) {
        push_to_tree(tree, rand1);

        rand1 = rand() % 100;
    }
}

void check(int *n) {
    printf("Введите число: ");
    int j = 0;
    while (1) {
        j = (scanf("%d", n));
        if (j == 1 && *n > 0)
            break;
        else
            printf("Ошибка, попробуй еще раз:");
        continue;
    }
}
void print() {
    printf("1: Добавить элемент в дерево:\n");
    printf("2: Добавить рандомное кол-во N элементов:\n");
    printf("3: Вывести дерево в консоль:\n");
    printf("6: Выйти из програми\n");
}