#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *fifo = "myfifo";        // Name of the FIFO file
    char msg[100];                // Buffer to store received message

    int fd = open(fifo, O_RDONLY); // Open FIFO in read-only mode

    printf("Reader: Waiting for message...\n");

    // Read message from FIFO into buffer
    read(fd, msg, sizeof(msg));

    // Display the received message
    printf("Reader: Message received -> %s\n", msg);

    close(fd);                    // Close file descriptor

    return 0;
}
