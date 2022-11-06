#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int rv;
    switch (pid = fork())
    {
    case -1:
        printf ("ERROR!");
        return 0;
        break;
    case 0:
        printf("fork procces %d\n", argc);
        break;    
    default:
        printf("parent procces %d\n", argc);
        wait(&rv);
        printf("Return status = %d\n", WEXITSTATUS(rv));
        break;
    }
    return 0;
}