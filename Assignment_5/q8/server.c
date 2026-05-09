#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8085);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 5);

    printf("Concurrent server running...\n");

    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        if(fork() == 0) {
            read(client_socket, buffer, sizeof(buffer));

            printf("Client says: %s\n", buffer);

            write(client_socket, "Message received", 17);

            close(client_socket);
            exit(0);
        }

        close(client_socket);
    }

    close(server_fd);
    return 0;
}
