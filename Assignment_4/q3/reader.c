#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char *ptr;

    fd = shm_open("/fileshm", O_RDONLY, 0666);

    ptr = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);

    printf("Reader: File Content from Shared Memory:\n\n");
    printf("%s\n", ptr);

    munmap(ptr, 1024);
    close(fd);

    shm_unlink("/fileshm");

    return 0;
}
