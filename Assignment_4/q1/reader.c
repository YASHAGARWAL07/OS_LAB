#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char *ptr;

    fd = shm_open("/myshm", O_RDONLY, 0666);

    ptr = mmap(0, 1024, PROT_READ, MAP_SHARED, fd, 0);

    printf("Message from shared memory: %s\n", ptr);

    munmap(ptr,1024);
    close(fd);

    shm_unlink("/myshm");

    return 0;
}
