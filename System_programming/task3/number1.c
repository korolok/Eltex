#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>


#define FIFO "/tmp/chat"

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};
int main(int argc, char *argv[]) {
    FILE *myfile;
    key_t key;
    pid_t pid;
    int semid = 0;
    char flag;
    srand(time(NULL));
    unlink(FIFO);
    union semun arg;
    struct sembuf lock_res = {0, -1, 0};
    struct sembuf rel_res = {0, 1, 0};
    key = ftok(".", 'v');
    semid = semget(key, 1, 0666 | IPC_CREAT);
    semop(semid, &rel_res, 1);
    if (key == -1 || semid == -1) {
        perror("ftok or semget");
    }
    
    if ((mkfifo(FIFO, 0777)) == -1) {
        perror("FIFO");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char quit = getchar();
        if (quit == 'q')
            break;
        semop(semid, &lock_res, 1);
        myfile = fopen(FIFO, "a");
        fprintf(myfile, "%d", rand() % 100);
        fclose(myfile);
        semop(semid, &rel_res, 1);
    }
    printf("no good\n");
    semctl(semid, 0, IPC_RMID);
    return 0;
}