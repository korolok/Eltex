#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[]) {
    FILE *myfile;
    
    for (int i = 1; 1; i++) {
        signal(SIGINT, SIG_IGN);
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