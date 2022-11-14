#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define NAME "sem"
static int count;
static pid_t pid = 0;
void listener(int sig);

int main(int argc, char *argv[]) {
    FILE *myfile;
    pid_t ppid = 0;
    key_t key;
    sem_t *semid;
    int fd[2], tmp = atoi(argv[1]), rv = 0, flag = 0;
    char buf[100];
    srand(time(NULL));
    pipe(fd);
    semid = sem_open(NAME, O_CREAT, 0600, 1);
    sem_post(semid);
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
                sem_trywait(semid);
                myfile = fopen("test.txt", "r");
                while (!feof(myfile)) {
                    fscanf(myfile, "%s", buf);
                }
                printf("%s\n", buf);
                fclose(myfile);
                sem_post(semid);
            }

        } else {
            close(fd[1]);
            read(fd[0], buf, sizeof(buf));
            sem_wait(semid);
            // semop(semid, &lock_res, 1);
            kill(ppid, SIGUSR1);
            myfile = fopen("test.txt", "a");
            fprintf(myfile, "%s", buf);
            fprintf(myfile, "%s", "\n");
            fclose(myfile);
            kill(ppid, SIGUSR2);
            // semop(semid, &rel_res, 1);
            sem_post(semid);
        }
        tmp--;
    }
    sem_close(semid);
    unlink(NAME);
    return 0;
}
void listener(int sig) {
    if (sig == SIGUSR1) {
        count = 1;
    } else if (sig == SIGUSR2) {
        count = 2;
    }
}