#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024
#define MSG_STOP "exit"

int main() {
    mqd_t mq;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq_unlink(QUEUE_NAME);

    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    char buffer[MAX_SIZE];

    while (1) {
        printf("Enter a message (or type 'exit' to quit): ");
        if (fgets(buffer, MAX_SIZE, stdin) == NULL || strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0) {
            break;
        }

        if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
            perror("mq_send");
            break;
        }
    }

    mq_close(mq);
    mq_unlink(QUEUE_NAME); // Optionally unlink the queue after use

    return 0;
}
