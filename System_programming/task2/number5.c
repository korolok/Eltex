#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int count = 0, flag = 0;
void listener(int sig);
int main(int argc, char *argv[]) {
    FILE *myfile;
    signal(SIGINT, listener);
    signal(SIGQUIT, listener);
    for (int i = 0; 1; i++) {
        char tmp[100];
        sprintf(tmp, "%d", i);
        myfile = fopen("test.txt", "a");
        if (myfile == NULL) {
            perror("File");
            return 0;
        }
        flag = 1;
        fprintf(myfile, tmp, strlen(tmp));
        fprintf(myfile, "%s", "\n");
        fclose(myfile);
        flag = 0;
        sleep(60);
        if (i >= 20) {
            break;
        }
    }
}
void listener(int sig) {
    if (flag == 1) {
        signal (SIGINT, SIG_IGN);
        signal (SIGQUIT, SIG_IGN);
    } else {
        signal (SIGINT, SIG_DFL);
        signal (SIGQUIT, SIG_DFL);
    }
}