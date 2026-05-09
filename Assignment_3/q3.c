#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(int arg,char *args[])
{
 if(arg<3)
 {
  printf("Enter source and destination\n");
  return 0;
 }

 int fd1=open(args[1],O_RDONLY);
 int fd2=open(args[2],O_CREAT|O_WRONLY,0644);

 char ch;

 while(read(fd1,&ch,1)>0)
 {
  write(fd2,&ch,1);
 }

 close(fd1);
 close(fd2);

 printf("File copied\n");

 return 0;
}
