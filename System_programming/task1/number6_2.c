#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    int myfile = 0;
    char buff[256];
    myfile = open(argv[1], O_RDWR);
    if (myfile == -1) {
        perror("file");
        return 0;
    }
    read(myfile, buff, 256);
    printf("%s\n", buff);
    close(myfile);
    return 0;
}