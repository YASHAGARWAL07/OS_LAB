#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
if(fork()==0)
exit(0);
else
sleep(60);
}
