#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char *ptr;

    fd = shm_open("/fileshm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 1024);

    ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    FILE *file = fopen("yash.txt", "r");

    if (file == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    fread(ptr, sizeof(char), 1024, file);

    printf("Writer: File content written to shared memory\n");

    fclose(file);
    munmap(ptr, 1024);
    close(fd);

    return 0;
}

