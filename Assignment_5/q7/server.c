#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void read_cpu(long long *idle, long long *total) {
    FILE *fp = fopen("/proc/stat", "r");
    long long user, nice, system, idle_t, iowait, irq, softirq, steal;

    fscanf(fp, "cpu %lld %lld %lld %lld %lld %lld %lld %lld",
           &user, &nice, &system, &idle_t, &iowait, &irq, &softirq, &steal);

    fclose(fp);

    *idle = idle_t + iowait;
    *total = user + nice + system + idle_t + iowait + irq + softirq + steal;
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8084);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("CPU Server running...\n");

    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        long long idle1, total1, idle2, total2;

        read_cpu(&idle1, &total1);
        sleep(1);
        read_cpu(&idle2, &total2);

        long long idle_diff = idle2 - idle1;
        long long total_diff = total2 - total1;

        float cpu_usage = (float)(total_diff - idle_diff) / total_diff * 100;

        char msg[100];
        sprintf(msg, "CPU Usage: %.2f%%", cpu_usage);

        write(client_socket, msg, strlen(msg) + 1);

        printf("Sent CPU usage to client\n");

        close(client_socket);
    }

    close(server_fd);
    return 0;
}
