#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char path[100], name[100];
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
    scanf("%s", name);
    getchar();
    if (-1 == execlp(str, name, NULL))
        perror("if failed");
    return 0;
}