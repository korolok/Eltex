#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define QUEUE_NAME "/my_queue"
#define PRIORITY 1

typedef struct mesgbuf {
    char msg_text[255];
} mesgbuf;

int main(int argc, char *argv[]) {
    mqd_t msqid = 0;
    int msglen = 0;
    char flag;
    srand(time(NULL));
    mesgbuf curr_rec_buf;
    mesgbuf curr_buf2;
    struct mq_attr queue_attr;
    queue_attr.mq_maxmsg = 10;
    queue_attr.mq_msgsize = sizeof(mesgbuf);

    msqid = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &queue_attr);
    while (1) {
        flag = getchar();
        sprintf(curr_buf2.msg_text, "%d", rand() % 100);
        msglen = strlen(curr_buf2.msg_text) + 1;
        if (mq_send(msqid, (char *)&curr_buf2, msglen, PRIORITY) == -1)
            perror("mq_send");
        
        mq_receive(msqid, (char *)&curr_rec_buf, sizeof(curr_rec_buf), NULL);
        if (0 == strncmp(curr_rec_buf.msg_text, "255", 3)) {
            printf("Exit\n");
            mq_close(msqid);
            return 0;
        } else
            printf("mqrsv = %s\n", curr_rec_buf.msg_text);
    }
    return 0;
}