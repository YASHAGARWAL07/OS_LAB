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

 int fd=open(args[1],O_RDONLY);
 char ch;

 while(read(fd,&ch,1)>0)
 {
  write(1,&ch,1);
 }

 close(fd);

 return 0;
}
