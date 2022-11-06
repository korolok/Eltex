#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv []) {
    int a1 = 0, a2 = 0;
    a1 = atoi(argv[0]);
    a2 = atoi(argv[1]);
    printf ("%d - %d = %d\n", a1, a2, a1 - a2);
    return 0;
}