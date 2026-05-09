#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char *fifo = "myfifo";        // Name of the FIFO file
    char msg[100];                // Buffer to store user input message

    mkfifo(fifo, 0666);           // Create named pipe (FIFO) with read/write permissions

    int fd = open(fifo, O_WRONLY); // Open FIFO in write-only mode

    printf("Writer: Enter message -> ");
    scanf(" %[^\n]", msg);

    // Write message into FIFO (strlen+1 to include '\0')
    write(fd, msg, strlen(msg) + 1);

    printf("Writer: Message sent successfully\n");

    close(fd);                    // Close file descriptor

    return 0;
}
