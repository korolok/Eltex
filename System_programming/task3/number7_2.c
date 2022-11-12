#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
int main(int argc, char *argv[]) {
    key_t key = atoi(argv[1]);
    pid_t pid;
    int size = atoi(argv[2]),
        shmid = 0,
        *s = NULL,
        *shm = NULL,
        max = 0,
        min = 1000;

    shmid = shmget(key, size, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    shm = shmat(shmid, 0, SHM_RND);
    if (shm == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    s = shm;
    for (int i = 0; i < size / sizeof(int); i++) {
        if (s[i] > max) {
            max = s[i];
        } else if (s[i] < min) {
            min = s[i];
        }
    }
    printf("max = %d\n", max);
    printf("min = %d\n", min);
    return 0;
}