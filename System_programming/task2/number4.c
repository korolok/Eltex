#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int count = 0;
void listener(int sig);
int main(int argc, char *argv[]) {
    FILE *myfile;
    signal(SIGINT, listener);
    signal(SIGQUIT, listener);
    for (int i = 0; count < 1; i++) {
        char tmp[100];
        sprintf(tmp, "%d", i);
        myfile = fopen("test.txt", "a");
        if (myfile == NULL) {
            perror("File");
            return 0;
        }
        fprintf(myfile, tmp, strlen(tmp));
        fprintf(myfile, "%s", "\n");
        fclose(myfile);
        sleep(60);
        if (i >= 20) {
            break;
        }
    }
}
void listener(int sig) {
    if (sig == 2) {
        printf("\nSignal SIGINT\n");
    }
    else if (sig == 3) {
        printf("\nSignal SIGQUIT\n");
    }
    count ++;
}