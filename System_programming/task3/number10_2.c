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
#include <string.h>
#define NAME "my_shm"

int main(int argc, char *argv[]) {
    key_t key = atoi(argv[1]);
    pid_t pid;
    int size = atoi(argv[2]),
        shmid = 0,
        *s = NULL,
        *shm = NULL,
        max = 0,
        min = 1000,
        res = 0;

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

        res += s[i];
    }
    if (strcmp(argv[3], "max") == 0) {
        printf("Максимальное значение: %d\n", max);
    } else if (strcmp(argv[3], "min") == 0) {
        printf("Минимальное значение: %d\n", min);
    } else if (strcmp(argv[3], "sum") == 0) {
        printf("Сумма всех чисел: %d\n", res);
    } else if (strcmp(argv[3], "mul") == 0) {
        res = res / (size / sizeof(int));
        printf("Среднее арифметическое всех чисел: %d\n", res);
    }
    return 0;
}