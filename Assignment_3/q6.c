#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Enter source and destination file\n");
        return 0;
    }

    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_CREAT | O_WRONLY, 0644);

    char ch;

    int pos = lseek(fd1, 0, SEEK_END);

    while(pos > 0)
    {
        lseek(fd1, -1, SEEK_CUR);
        read(fd1, &ch, 1);
        write(fd2, &ch, 1);
        lseek(fd1, -1, SEEK_CUR);
        pos--;
    }

    close(fd1);
    close(fd2);

    printf("File reversed successfully\n");

    return 0;
}
