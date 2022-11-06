#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#define FIFO "/tmp/chat"
int main(int argc, char *argv[]) {
    FILE *myfile;
    char buf[256];
    while (1) {
        myfile = fopen(FIFO, "r");
        fread(buf, 256, 256, myfile);
        printf("%s\n", buf);
        fclose(myfile);
    }
    exit(EXIT_SUCCESS);
    return 0;
}