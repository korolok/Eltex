#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    int fd1[2], fd2[2], tmp = atoi(argv[1]), var = 0, rv = 0;
    char buf[100], buf2[100];
    pid_t pid;
    FILE *myfile;
    srand(time(NULL));      
    pipe(fd1);
    pipe(fd2);
    pid = fork();
     printf("pid = [%d]\n", pid);
    if (pid == -1) {
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    while (tmp != 0) {
        if (pid == 0) {
            printf("chid pid %d\n", getpid());
            close(fd1[1]);
            close(fd2[0]);
            sprintf(buf, "%d", rand() % 100);
            write(fd2[1], buf, strlen(buf) + 1);
            read(fd1[0], buf2, sizeof(buf2));
            var = atoi(buf2);
            printf("Number multiplied by 2: %d\n", var * 2);

        } else {
            printf("paent pid %d\n", getpid());
            close(fd1[0]);
            close(fd2[1]);
            read(fd2[0], buf, sizeof(buf));
            printf("%s\n", buf);
            myfile = fopen("test.txt", "a");
            fprintf(myfile, "%s", buf);
            fprintf(myfile, "%s", "\n");
            fclose(myfile);
            var = atoi(buf);
            sprintf(buf2, "%d", var);
            write(fd1[1], buf2, strlen(buf) + 1);
        }
        tmp--;
    }
    return 0;
}