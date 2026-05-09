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
    address.sin_port = htons(8082);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    printf("Waiting for connection...\n");

    client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    read(client_socket, buffer, sizeof(buffer));

    printf("Request received: %s\n", buffer);

    for(int i = 0; buffer[i]; i++) {
        if(buffer[i] >= 'a' && buffer[i] <= 'z') {
            buffer[i] = buffer[i] - 32;
        }
    }

    printf("Converted to uppercase: %s\n", buffer);

    write(client_socket, buffer, strlen(buffer) + 1);

    printf("Response sent to client\n");

    close(client_socket);
    close(server_fd);

    return 0;
}
