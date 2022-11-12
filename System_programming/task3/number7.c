#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
static int flag = 0;
void listener(int sig);
int main(int argc, char *argv[]) {
    key_t key;
    pid_t pid;
    srand(time(NULL));
    int shmid = 0,
        semid = 0,
        size = sizeof(int) * (rand() % 10000),
        *s = NULL,
        *shm = NULL;
    char nkey[64],
        nsize[64];
    signal(SIGINT, listener);
    struct sembuf lock_res = {0, -1, 0};
    struct sembuf rel_res = {0, 1, 0};
    key = ftok(".", 'o');
    if (key == -1) {
        perror("ftok1");
        exit(EXIT_FAILURE);
    }
    semid = semget(key, 1, 0666 | IPC_CREAT);
    semop(semid, &rel_res, 1);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    shmid = shmget(key, size, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget1");
        exit(EXIT_FAILURE);
    }
    shm = shmat(shmid, 0, SHM_RND);
    if (shm == (int *)-1) {
        perror("shmat1");
        exit(EXIT_FAILURE);
    }
    s = shm;

    semop(semid, &lock_res, 1);
    while (1) {
        sleep(3);
        for (int i = 0; i < (size / sizeof(int)); i++) {
            s[i] = rand() % 10000;
        }
        semop(semid, &rel_res, 1);

        sprintf(nkey, "%d", key);
        sprintf(nsize, "%d", size);
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execl("./fork", "fork", nkey, nsize, NULL);
        }
        if (flag == 1) {
            printf("Работа завершена сигналом SIGINT\n");
            break;
        }
    }

    wait(NULL);
    shmdt(0);
    semctl(semid, 0, IPC_RMID);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
void listener(int sig) {
    if (sig == SIGINT) {
        flag++;
    }
}