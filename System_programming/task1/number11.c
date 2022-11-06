#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIFO "/tmp/chat"

int main(int argc, char *argv[]) {
    FILE *myfile;
    char flag;
    srand(time(NULL));
    unlink(FIFO);
    if ((mkfifo(FIFO, 0777)) == -1) {
        perror("FIFO");
        exit(EXIT_FAILURE);
    }
    while (1) {
        int quit = getchar();
        if (quit == 'q')
            return 0;
        myfile = fopen(FIFO, "a");
        fprintf(myfile, "%d", rand() % 100);
        fclose(myfile);
    }
    exit(EXIT_SUCCESS);
    return 0;
}