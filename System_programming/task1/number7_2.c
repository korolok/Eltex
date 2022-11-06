#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    FILE *myfile;
    char buff[256];
    myfile = fopen(argv[1], "r");
    if (myfile == NULL) {
        perror("file");
        return 0;
    }
    fread(buff, 256, 256, myfile);
    printf("%s\n", buff);
    fclose(myfile);
    return 0;
}