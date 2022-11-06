#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>
#include <string.h>

#include "msg.h"
int main(int argc, char *argv[]) {
    msgbuf msg = {};
    int msqid = 0,
        key = ftok(".", 'k');
    int lenght = sizeof(msgbuf) - sizeof(long);
    msqid = msgget(key, IPC_CREAT | 0666);
    while (1) {
        msgrcv(msqid, (msgbuf *)&msg, lenght, 1, 0);
        if (0 == strncmp(msg.mtext, "255", 3)) {
            printf ("Exit\n");
            msgctl(msqid, IPC_RMID, NULL);
            return 0;
        }
        else printf("msgrsv = %s\n", msg.mtext);
    }
    return 0;
}