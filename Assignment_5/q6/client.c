#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8083);
    server.sin_addr.s_addr = inet_addr("10.141.218.13");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    read(sock, buffer, sizeof(buffer));

    printf("Updated Client Table:\n%s", buffer);

    close(sock);

    return 0;
}
