#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "msg.h"

int main(int argc, char *argv[]) {
    msgbuf msg = {};
    msgbuf msg2 = {};
    int msqid = 0,
        key = ftok(".", 'k');
    int lenght = 0;
    char tmp[200];
    msg2.mtype = 1;
    msg.mtype = 1;
    msqid = msgget(key, IPC_CREAT | 0666);
    lenght = sizeof(msgbuf) - sizeof(long);
    while (1) {
        msgrcv(msqid, (struct msgbuf *)&msg2, lenght, 1, 0);
        printf("%s\n", msg2.mtext);

        scanf("%s", tmp);
        strncpy(msg.mtext, tmp, 200);

        msgsnd(msqid, (struct msgbuf *)&msg, lenght, 0);
    }

    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}
