#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int check(int *, int *, int *, int *, int);

int main() {
    int a = 0,  // размеры ёмкостей константы
        b = 0,
        c = 0,
        a1 = 0,  // размеры ёмкостей не константы
        b1 = 0,
        c1 = 0,
        K = 8,      // размер заполненной ёмкости
        count = 0,  // counter
        tmp = 0,    // счетчик остатка
        R = 4;      // нужный объем
    printf("Введите объем 3 емкостей: ");
    check(&a, &b, &c, NULL, 1);
    a1 = a;
    b1 = b;
    c1 = c;
    printf("Введите размер заполненой емкости: ");
    count = check(&a, &b, &c, &K, 2);
    printf("Введите объём, который необходимо достичь в одной из ёмкостей: ");
    check(&R, &b, NULL, NULL, 3);
    if (count == 1) {
        b1 = 0;
        c1 = 0;
    } else if (count == 2) {
        a1 = 0;
        c1 = 0;
    } else if (count == 3) {
        a1 = 0;
        b1 = 0;
    }
    for (int i = 0; 1; i++) {
        a1 -= c;
        c1 += c;
        tmp = b - b1;
        if (tmp >= c) {
            b1 += c;
            c1 -= c;
        } else {
            c1 -= tmp;
            b1 += tmp;
            a1 += b;
            b1 -= b;
            b1 += c1;
            c1 = 0;
        }
        if (a1 == R || b1 == R || c1 == R) {
            printf("На решение задачи ушло %d итераций\n", R);
            printf("%d %d %d\n", a1, b1, c1);
            break;
        }
    }
    return 0;
}
int check(int *pa, int *pb, int *pc, int *K, int flag) {
    int count = 0;
    if (flag == 1) {
        while (1) {
            count = scanf("%d%d%d", pa, pb, pc);
            getchar();
            if (count == 3 && *pa > 0 && *pb > 0 && *pc > 0 && *pa > *pb && *pb > *pc) {
                break;
            } else {
                printf("Ошибка, поробуй еще раз: ");
            }
        }
    }
    if (flag == 2) {
        while (1) {
            count = scanf("%d", K);
            getchar();
            if (count == 1 && *K > 0 && *K == *pa) {
                if (*K == *pa) {
                    return 1;
                } else if (*K == *pb) {
                    return 2;
                } else if (*K == *pc) {
                    return 3;
                } else {
                    printf("Ошибка, поробуй еще раз: ");
                }
            } else {
                printf("Ошибка, поробуй еще раз: ");
            }
        }
    }
    if (flag == 3) {
        while (1) {
            count = scanf("%d", pa);
            getchar();
            if (count == 1 && *pa > 0 && *pb > *pa) {
                break;
            } else {
                printf("Ошибка, поробуй еще раз: ");
            }
        }
    }
    return 0;
}
