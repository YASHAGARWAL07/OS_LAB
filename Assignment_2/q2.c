#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Please provide array size in command line\n");
        return 1;
    }

    int size = atoi(argv[1]);

    int arr[size];

    int max = 2000, min = 2;

    srand(time(NULL));

    printf("Generated array:\n");

    for(int i = 0; i < size; i++)
    {
        arr[i] = (rand() % (max - min + 1)) + min;
        printf("%d ", arr[i]);
    }

    printf("\n");

    pid_t pid = fork();

    if(pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    else if(pid == 0) // Child process → even sum
    {
        int even_sum = 0;

        for(int i = 0; i < size; i++)
        {
            if(arr[i] % 2 == 0)
            {
                even_sum += arr[i];
            }
        }

        printf("Even sum = %d\n", even_sum);
        exit(0);
    }

    else // Parent process → odd sum
    {
        int odd_sum = 0;

        for(int i = 0; i < size; i++)
        {
            if(arr[i] % 2 != 0)
            {
                odd_sum += arr[i];
            }
        }

        printf("Odd sum = %d\n", odd_sum);

        wait(NULL);
    }

    return 0;
}
