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
#include <sys/mman.h>
#define NAME "my_shm"

int main(int argc, char *argv[]) {
    key_t key = atoi(argv[1]);
    pid_t pid;
    int size = atoi(argv[2]),
        shmid = 0,
        *s = NULL,
        *shm = NULL,
        max = 0,
        min = 1000;

    shmid = shm_open(NAME, O_RDWR, 0666);
    if (shmid == -1) perror("shm_open");
    shm = mmap(0, size, PROT_WRITE, MAP_SHARED, shmid, 0);
    if (shm  == (int *)-1) perror("mmap");
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