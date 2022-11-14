#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <semaphore.h>
#define FIFO "chat"


int main(int argc, char *argv[]) {
    FILE *myfile;
    sem_t *semid;
    char flag;
    srand(time(NULL));
    unlink(FIFO);
    semid = sem_open(FIFO, O_CREAT, 0600, 1);
    if (semid == (sem_t *)(-1)) perror("sem");
    sem_post(semid);
    if ((mkfifo(FIFO, 0777)) == -1) {
        perror("FIFO");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char quit = getchar();
        if (quit == 'q')
            break;
        sem_wait(semid);
        myfile = fopen(FIFO, "a");
        fprintf(myfile, "%d", rand() % 100);
        fclose(myfile);
        sem_post(semid);
    }
    printf("no good\n");
    sem_close(semid);
    unlink(FIFO);
    return 0;
}