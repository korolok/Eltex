#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#define NAME "my_shm"

const char *flags[] = {"max", "min", "sum", "mul"};
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

    shmid = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    if (shmid == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(shmid, size + 1) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }
    shm = mmap(0, size, PROT_WRITE, MAP_SHARED, shmid, 0);
    if (shm == (int *)-1) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    s = shm;

    semop(semid, &lock_res, 1);
    while (1) {
        int i = 0;
        sleep(3);
        for (int i = 0; i < (size / sizeof(int)); i++) {
            s[i] = rand() % 10000;
        }
        semop(semid, &rel_res, 1);

        sprintf(nkey, "%d", key);
        sprintf(nsize, "%d", size);
        for (int i = 0; i < 4; i++) {
            pid = fork();
            if (-1 == pid) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (0 == pid) {
                int rc;
                if (-1 == execl("./hello", "fork", nkey, nsize, flags[i], NULL)) {
                    perror("exec");
                }
                exit(5);
            }
        }
        if (flag == 1) {
            printf("???????????? ?????????????????? ???????????????? SIGINT\n");
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