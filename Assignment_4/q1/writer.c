#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char *ptr;
    char msg[100];

    fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);

    ftruncate(fd, 1024);

    ptr = mmap(0, 1024, PROT_WRITE, MAP_SHARED, fd, 0);

    printf("Enter message: ");
    scanf(" %[^\n]", msg);

    strcpy(ptr, msg);

    printf("Message written to shared memory\n");
    int x;
    scanf("%d", &x);
    munmap(ptr,1024);
    close(fd);

    return 0;
}
