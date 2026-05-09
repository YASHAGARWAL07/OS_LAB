#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
int status;
if(fork()==0)
exit(10);
else
{
wait(&status);
printf("Exit status=%d\n", WEXITSTATUS(status));
}
}
