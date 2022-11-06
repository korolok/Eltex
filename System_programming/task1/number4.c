#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int a1, a2;
    char path[100];
    FILE *myfile;
    char str[100];
    system("pwd>test.txt");
    myfile = fopen("test.txt", "r");
    fscanf(myfile, "%s", str);
    printf("Programm difference of numbers\n");
    printf("<< ");
    scanf("%s", path);
    getchar();
    strcat(str, path);
    a1 = getchar();
    getchar();
    a2 = getchar();
    if (-1 == execlp(str, (char *)&a1, (char *)&a2, NULL))
        perror("if failed");
    return 0;
}