#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char msg[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8081);
    server.sin_addr.s_addr = inet_addr("10.141.218.13");

    printf("Enter message: ");
    scanf(" %[^\n]", msg);

    sendto(sock, msg, strlen(msg) + 1, 0, (struct sockaddr *)&server, sizeof(server));

    printf("Message sent!\n");

    close(sock);

    return 0;
}

