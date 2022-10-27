#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct node {
    int data;
    struct node *next;
} node;
void push_tail(node *, int);
void print_list_head(node *);
void push_head(node **, int);
int pop_to_tail(node *);
int pop_to_head(node **);
void print_list_tail(node *);
int edit_to_head(node *, int);
int edit_to_tail(node *, int);
void rand_list(node *, int);
void check(int *);
void clear_list(node *);
void sort_buble_list(node *);
void comb_sort_list(node *, int);
void print();

int main() {
    int n = 0,
        count = 0,
        edit1 = 0,
        number = 0;
    node *list = (node *)malloc(sizeof(node)); 
    while (1) {
        print();
        check(&count);
        switch (count) {
            case 1:
                check(&number);
                push_head(&list, number);
                n++;
                printf("\n");
                break;
            case 2:
                check(&number);
                push_tail(list, number);
                n++;
                printf("\n");
                break;
            case 3:
                printf("Remove element: %d\n", pop_to_head(&list));
                if (n > 0) {
                    n--;
                }
                printf("\n");
                break;
            case 4:
                printf("Remove element: %d\n", pop_to_tail(list));
                if (n > 0) {
                    n--;
                }
                printf("\n");
                break;
            case 5:
                printf("Ведетите элемент на который хотите заменить\n");
                check(&edit1);
                printf ("Edit element: %d\n", edit_to_head(list, edit1));
                printf("\n");
                break;
            case 6:
                printf("Ведетите элемент на который хотите заменить\n");
                check(&edit1);
                printf ("Edit element: %d\n", edit_to_tail(list, edit1));
                printf("\n");
                break;
            case 7:
                print_list_head(list);
                printf("\n");
                break;
            case 8:
                print_list_tail(list);
                printf("\n");
                break;
            case 9:
                check(&n);
                rand_list(list, n);
                printf("\n");
                break;
            case 10:
                sort_buble_list(list);
                printf("\n");
                break;
            case 11:
                comb_sort_list(list, n);
                printf("\n");
                break;
            default:
                break;
        }
        if (count == 13) {
            free(list);
            break;
        }
    }
    return 0;
}
void push_tail(node *list, int data) {
    node *tmp = (node *)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = NULL;
    while (list->next != NULL) list = list->next;
    list->next = tmp;
}
void print_list_head(node *list) {
    node *p = list;
    while (p != NULL) {
        printf("%d\n", p->data);
        p = p->next;
    }
}
void push_head(node **list, int data) {
    node *tmp = (node *)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = *list;
    *list = tmp;
}
int pop_to_tail(node *list) {
    if (list->next == NULL) {
        printf("Element to remove doesn't exist. List is empty.\n");
    } else {
        int var = 0;
        node *tmp = list;
        while (list->next != NULL) {
            list = list->next;
            tmp = list;
        }
        var = tmp->data;
        tmp->next = NULL;
        free(list);
        return var;
    }
}
int pop_to_head(node **list) {
    if ((*list)->next == NULL) {
        printf("Element to remove doesn't exist. List is empty.\n");
    } else {
        int var = 0;
        node *tmp = *list;
        var = tmp->data;
        *list = tmp->next;
        free(tmp);
        return var;
    }
}

void print_list_tail(node *list) {
    if (list != NULL) {
        print_list_tail(list->next);
        printf("%d\n", list->data);
    }
}
int edit_to_head(node *list, int n) {
    if (list->next == NULL) {
        printf("Element to remove doesn't exist. List is empty.\n");
    } else {
    int res = list->data;
    list->data = n;
    return res;
    }
}
int edit_to_tail(node *list, int n) {
    if (list == NULL) {
        printf("Element to remove doesn't exist. List is empty.\n");
    } else {
    while (list->next != NULL) {
        list = list->next;
    }
    int res = list->data;
    list->data = n;
    return res;
    }
}
void rand_list(node *list, int n) {
    srand(time(NULL));
    int rand1 = n;
    for (int i = 1; i < n; i++) {
        push_tail(list, rand1);

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

void clear_list(node *list) {
    if (list != NULL) {
        clear_list(list->next);
        free(list->next);
    }
}

void sort_buble_list(node *list) {
    node *tmp1 = list;
    node *tmp2 = list;
    for (tmp1; tmp1->next != NULL; tmp1 = tmp1->next) {
        node *tmp2 = list;
        for (tmp2; tmp2->next != NULL; tmp2 = tmp2->next) {
            if (tmp2->data > tmp2->next->data) {
                int var = tmp2->data;
                tmp2->data = tmp2->next->data;
                tmp2->next->data = var;
            }
        }
    }
}

void comb_sort_list(node *list, int n) {
    double factor = 1.2473309;  // фактор уменьшения
    int step = n - 1;           // шаг сортировки

    while (step >= 1) {
        node *p1 = list;
        node *p2 = list;
        for (int i = 0; i < step; i++) p2 = p2->next;
        for (int i = 0; i + step < n; i++, p1 = p1->next, p2 = p2->next) {
            if (p1->data < p2->data) {
                int temp = p1->data;
                p1->data = p2->data;
                p2->data = temp;
            }
        }
        step /= factor;
    }
}

void print() {
    printf("1: чтобы добавить узел в начало\n");
    printf("2: чтобы добавить узел в конец\n");
    printf("3: чтобы удалить узел  сначала\n");
    printf("4: чтобы удалить узел с конца\n");
    printf("5: чтобы редактировать узел с начала\n");
    printf("6: чтобы редактировать узел с конца\n");
    printf("7: чтобы вывести в консоль с начала\n");
    printf("8: чтобы вывести в консоль с конца\n");
    printf("9: функция заполнения списка N случайными числами;\n");
    printf("10: отсортировать список вверх\n");
    printf("11: отсортировать список вниз\n");
    printf("13: чтобы выйти и очистить память\n");
    printf("\n");
}
