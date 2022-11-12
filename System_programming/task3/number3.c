#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>`
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

static int count;
static pid_t pid = 0;
void listener(int sig);

int main(int argc, char *argv[]) {
    FILE *myfile;
    pid_t ppid = 0;
    key_t key;
    int semid = 0;
    int fd[2], tmp = atoi(argv[1]), rv = 0, flag = 0;
    char buf[100];
    union semun arg;
    struct sembuf lock_res = {0, -1, 0};
    struct sembuf rel_res = {0, 1, 0};
    srand(time(NULL));
    pipe(fd);
    key = ftok(".", 'v');
    semid = semget(key, 1, 0666 | IPC_CREAT);
    semop(semid, &rel_res, 1);
    if (key == -1 || semid == -1) {
        perror("ftok or semget");
    }

    while (tmp != 0) {
        ppid = fork();
        if (ppid == -1) {
            perror("Fork");
            return 0;
        }
        signal(SIGUSR1, listener);
        signal(SIGUSR2, listener);
        if (ppid == 0) {
            pid = getpid();
            close(fd[0]);
            sprintf(buf, "%d", rand() % 100);
            write(fd[1], buf, strlen(buf) + 1);
            printf("count = %d\n", count);
            if (count == 2) {
                // semop(semid, &lock_res, 1);
                myfile = fopen("test.txt", "r");
                while (!feof(myfile)) {
                    fscanf(myfile, "%s", buf);
                }
                printf("%s\n", buf);
                fclose(myfile);
                // semop(semid, &rel_res, 1);
            }

        } else {
            close(fd[1]);
            read(fd[0], buf, sizeof(buf));
            semop(semid, &lock_res, 1);
            kill(ppid, SIGUSR1);
            myfile = fopen("test.txt", "a");
            fprintf(myfile, "%s", buf);
            fprintf(myfile, "%s", "\n");
            fclose(myfile);
            kill(ppid, SIGUSR2);
            semop(semid, &rel_res, 1);
        }
        tmp--;
    }
    semctl(semid, 0, IPC_RMID);
    return 0;
}
void listener(int sig) {
    if (sig == SIGUSR1) {
        count = 1;
    } else if (sig == SIGUSR2) {
        count = 2;
    }
}