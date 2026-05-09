#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock;
    struct sockaddr_un addr;
    char msg[100];

    sock = socket(AF_UNIX, SOCK_STREAM, 0); // Create socket

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "mysocket"); // Same path as server

    connect(sock, (struct sockaddr*)&addr, sizeof(addr)); // Connect to server

    scanf(" %[^\n]", msg); // Take input

    write(sock, msg, strlen(msg) + 1); // Send message

    close(sock);

    return 0;
}


