#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(int arg,char *args[])
{
 if(arg<2)
 {
  printf("Enter file name\n");
  return 0;
 }

 int fd=open(args[1],O_CREAT,0644);

 if(fd<0)
  printf("File not created\n");
 else
  printf("File created\n");

 close(fd);

 return 0;
}
