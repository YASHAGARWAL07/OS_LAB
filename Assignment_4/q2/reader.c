#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

struct shared_data
{
    int flag;
    char message[100];
};

int main()
{
    int fd;
    struct shared_data *ptr;

    fd = shm_open("/syncmem", O_RDWR, 0666);

    ptr = mmap(NULL, sizeof(struct shared_data),
               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    while(ptr->flag != 1);

    printf("Reader received: %s\n", ptr->message);

    ptr->flag = 2;

    munmap(ptr, sizeof(struct shared_data));
    close(fd);

    shm_unlink("/syncmem");

    return 0;
}


