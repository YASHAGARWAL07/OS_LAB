#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    if(argc < 2)
    {
        printf("Please provide a Linux command\n");
        return 1;
    }

    pid = fork();

    if(pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }

    else if(pid == 0)   // Child process
    {
        printf("Executing command...\n");

        execvp(argv[1], &argv[1]);

        printf("Exec failed\n");
        exit(1);
    }

    else   // Parent process
    {
        wait(NULL);
        printf("Child process completed\n");
    }

    return 0;
}
