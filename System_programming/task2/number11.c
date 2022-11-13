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

typedef struct mesgbuf
{
    char msg_text[255];
} mesgbuf;

int main(int argc, char *argv[]) {
    mqd_t msqid = 0;
    int msglen = 0;
    char flag;
    srand(time(NULL));
    mesgbuf curr_buf;
    mesgbuf curr_rec_buf2;
    struct mq_attr queue_attr;
    queue_attr.mq_maxmsg = 10;
    queue_attr.mq_msgsize = sizeof(mesgbuf);

    msqid = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &queue_attr);
    if (msqid == (mqd_t)-1) {
        perror("mq_open");
    }
    printf("Print q for quit\n");
    while (1) {
        flag = getchar();

        if (flag == 'q') {
            sprintf(curr_buf.msg_text, "%d", 255);
            msglen = strlen(curr_buf.msg_text) + 1;
            mq_send(msqid, (char *)&curr_buf, msglen, PRIORITY);
            exit(EXIT_SUCCESS);
        } else {
            mq_receive(msqid, (char *)&curr_rec_buf2, sizeof(curr_rec_buf2) + 1, NULL);
            printf("mqrsv = %s\n", curr_rec_buf2.msg_text);
            sprintf(curr_buf.msg_text, "%d", rand() % 100);
            msglen = strlen(curr_buf.msg_text) + 1;
            if (mq_send(msqid, (char *)&curr_buf, msglen, PRIORITY) == -1)
                perror("mq_send");
        }
    }
    if(mq_close(msqid) == -1)
    {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }
    return 0;
}