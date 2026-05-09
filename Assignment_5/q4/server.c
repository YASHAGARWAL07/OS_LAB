#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[100];

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0); // Create socket

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "mysocket"); // File path for socket

    unlink("mysocket"); // remove old socket file

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)); // Bind socket

    listen(server_fd, 5); // Listen for connections

    printf("Waiting for client...\n");

    client_fd = accept(server_fd, NULL, NULL); // Accept client

    int n = read(client_fd, buffer, sizeof(buffer)); // Read data

    if(n > 0) {
        buffer[n] = '\0';
        printf("Message Received : %s\n", buffer); // Print message
    }

    close(client_fd);
    close(server_fd);

    return 0;
}

