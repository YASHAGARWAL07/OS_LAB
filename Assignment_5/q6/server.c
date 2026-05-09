#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct client_info {
    char ip[20];
    int port;
};

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address, client_addr;
    int addrlen = sizeof(client_addr);
    struct client_info clients[10];
    int count = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8083);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server started...\n");

    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen);

        strcpy(clients[count].ip, inet_ntoa(client_addr.sin_addr));
        clients[count].port = ntohs(client_addr.sin_port);
        count++;

        printf("Client connected: %s : %d\n", clients[count-1].ip, clients[count-1].port);

        char table[1024] = "";
        strcat(table, "Client No\tIP Address\tPort\n");

        for(int i = 0; i < count; i++) {
            char temp[100];
            sprintf(temp, "%d\t\t%s\t%d\n", i+1, clients[i].ip, clients[i].port);
            strcat(table, temp);
        }

        write(client_socket, table, strlen(table) + 1);

        close(client_socket);
    }

    close(server_fd);
    return 0;
}
