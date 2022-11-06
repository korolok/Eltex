#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    FILE *myfile;
    char buff[256];
    myfile = fopen(argv[1], "a");
    if (myfile == NULL) {
        perror("file");
        return 0;
    }
    scanf("%s", buff);
    fprintf(myfile, buff, strlen(buff));
    fprintf(myfile, "%s", "\n");
    fclose(myfile);
    return 0;
}