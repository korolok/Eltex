#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
#include "msg.h"
int main(int argc, char *argv[]) {
    msgbuf msg = {};
    int msqid = 0,
        key = ftok(".", 'k');
    char flag;
    int lenght = 0;
    srand(time(NULL));
    
    msg.mtype = 1 ;
    strncpy(msg.mtext, "hi", 200);

    msqid = msgget(key, IPC_CREAT | 0666);
    printf("Print q for quit\n");
    lenght = sizeof(msgbuf) - sizeof(long);
    while (1) {
        flag = getchar();
        
        if (flag == 'q') {
            sprintf(msg.mtext, "%d", 255);
            msgsnd(msqid, (struct msgbuf *)&msg, lenght, 0);
            msgctl(msqid, IPC_RMID, NULL);
            exit (EXIT_SUCCESS);
        } else {
            sprintf(msg.mtext, "%d", rand() % 100);
            if(msgsnd(msqid, (struct msgbuf *)&msg, lenght, 0) == -1)
            perror("msgsnd");
        }
    }
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}