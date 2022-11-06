#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int rv = 0;
    int num ;
    switch (pid = fork())
    {
    case -1: 
        exit(EXIT_FAILURE);
    case 0:
        for (int i = (argc / 2) + 1; i < argc; i++) {
            num = atoi(argv[i]);
            printf("Element = [%d], square = %d\n", num, num * num);
        }
        exit(EXIT_SUCCESS);
    default:
        for (int i = 1; i < argc/2 + 1; i++) {
            num = atoi(argv[i]);
            printf("Element = [%d], square = %d\n", num, num * num);
        }
        wait(&rv);
    }
    exit(EXIT_SUCCESS);
    return 0;
}