#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
    int status;
    pid_t pid = fork();

    if(pid == 0)
    {
        printf("Child Process Running...\n");
        exit(10);   // Exit status
    }
    else
    {
        wait(&status);

        if(WIFEXITED(status))
        {
            printf("Child exited normally\n");
            printf("Exit Status = %d\n", WEXITSTATUS(status));
        }

        if(WIFSIGNALED(status))
        {
            printf("Child terminated by signal\n");
            printf("Signal Number = %d\n", WTERMSIG(status));
        }

        if(WIFSTOPPED(status))
        {
            printf("Child stopped\n");
        }
    }

    return 0;
}
