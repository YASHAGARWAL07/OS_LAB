#include<stdio.h>
#include<unistd.h>

int main()
{
    int pid = fork();

    if(pid == 0)
    {
        sleep(2);   // Child runs after parent
        printf("Child PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else
    {
        printf("Parent PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}
