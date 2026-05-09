#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    char write_msg[] = "Hello from Parent Process";
    char read_msg[100];

    pipe(fd); // create pipe

    int pid = fork();

    if (pid > 0)
    {
        // Parent Process
        close(fd[0]); // close read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        printf("Parent sent: %s\n", write_msg);
        close(fd[1]);
    }
    else
    {
        // Child Process
        close(fd[1]); // close write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);
    }

    return 0;
}

