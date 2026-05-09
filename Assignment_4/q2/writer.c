#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct shared_data
{
    int flag;
    char message[100];
};

int main()
{
    int fd;
    struct shared_data *ptr;

    fd = shm_open("/syncmem", O_CREAT | O_RDWR, 0666);

    ftruncate(fd, sizeof(struct shared_data));

    ptr = mmap(NULL, sizeof(struct shared_data),
               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("Enter message: ");
    scanf(" %[^\n]", ptr->message);

    ptr->flag = 1;

    printf("Writer: Message written\n");

    while(ptr->flag != 2);

    printf("Reader has read the message\n");

    munmap(ptr, sizeof(struct shared_data));
    close(fd);

    return 0;
}

