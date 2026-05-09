#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock;
    struct sockaddr_in server, client;
    char buffer[1024];
    socklen_t len;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8081);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Waiting for message...\n");

    len = sizeof(client);
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &len);

    printf("Message from client: %s\n", buffer);

    close(sock);

    return 0;
}
