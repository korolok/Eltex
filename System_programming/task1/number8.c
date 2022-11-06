#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    FILE *myfile;
    pid_t ppid = 0;
    int fd[2], tmp = atoi(argv[1]), rv = 0;
    char buf[100];
    srand(time(NULL));
    pipe(fd);
    ppid = fork();
    if (ppid == -1) {
        perror("Fork");
        return 0;
    }
    while (tmp != 0) {
        if (ppid == 0) {
            close(fd[0]);
            sprintf(buf, "%d", rand() % 100);
            write(fd[1], buf, strlen(buf) + 1);
            usleep(500);
        } else {
            close(fd[1]);
            read(fd[0], buf, sizeof(buf));
            printf("%s\n", buf);
            myfile = fopen("test.txt", "a");
            fprintf(myfile, "%s", buf);
            fprintf(myfile, "%s", "\n");
            fclose(myfile);
        }
        tmp--;
    }
    return 0;
}
