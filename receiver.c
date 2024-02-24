#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024

int main()
{
    mqd_t mq;
    char buffer[MAX_SIZE + 1]; // Ensure space for null-terminator

    // Open the message queue
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == -1)
    {
        perror("mq_open");
        exit(1);
    }

    // Receive the message
    while (1)
    {

        if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1)
        {
            perror("mq_receive");
            // mq_close(mq); // Ensure to close mq before exiting
            // exit(1);
        }
        else
        {
            buffer[MAX_SIZE] = '\0'; // Ensure the string is null-terminated
            printf("Received message: %s\n", buffer);
        }
    }

    // Close the message queue
    mq_close(mq);

    return 0;
}
