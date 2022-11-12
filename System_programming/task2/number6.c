#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
static int count;
static pid_t pid = 0;
void listener(int sig);
int main(int argc, char *argv[]) {
    FILE *myfile;
    pid_t ppid = 0;
    int fd[2], tmp = atoi(argv[1]), rv = 0, flag = 0;
    char buf[100];
    srand(time(NULL));
    pipe(fd);
    ppid = fork();
    if (ppid == -1) {
        perror("Fork");
        return 0;
    }

    while (tmp != 0) {
        signal(SIGUSR1, listener);
        signal(SIGUSR2, listener);
        if (ppid == 0) {
            pid = getpid();
            close(fd[0]);
            sprintf(buf, "%d", rand() % 100);
            write(fd[1], buf, strlen(buf) + 1);
            printf("count = %d\n", count);
            if (count == 2) {
                myfile = fopen("test.txt", "r");
                while (!feof(myfile)) {
                    fscanf(myfile, "%s", buf);
                }
                printf("%s\n", buf);
                fclose(myfile);
                usleep(500);
            }

        } else {
            close(fd[1]);
            read(fd[0], buf, sizeof(buf));
            kill(ppid, SIGUSR1);
            myfile = fopen("test.txt", "a");
            fprintf(myfile, "%s", buf);
            fprintf(myfile, "%s", "\n");
            fclose(myfile);
            kill(ppid, SIGUSR2);
        }
        tmp--;
    }
    return 0;
}
void listener(int sig) {
    if (sig == SIGUSR1) {
        count = 1;
    } else if (sig == SIGUSR2) {
        count = 2;
    }
}