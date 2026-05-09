#include <stdio.h>
#include <unistd.h>

int main()
{
    int pipe1[2], pipe2[2];
    pipe(pipe1); // parent to child
    pipe(pipe2); // child to parent

    int pid = fork();

    if (pid > 0)
    {
        // Parent Process
        int n, arr[100], key, result;

        printf("Enter array size: ");
        scanf("%d", &n);

        printf("Enter array elements: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        printf("Enter element to search: ");
        scanf("%d", &key);

        close(pipe1[0]); // close read end
        write(pipe1[1], &n, sizeof(n));
        write(pipe1[1], arr, sizeof(arr));
        write(pipe1[1], &key, sizeof(key));
        close(pipe1[1]);

        close(pipe2[1]); // close write end
        read(pipe2[0], &result, sizeof(result));

        if (result == 1)
            printf("Element Found\n");
        else
            printf("Element Not Found\n");

        close(pipe2[0]);
    }
    else
    {
        // Child Process
        int n, arr[100], key, found = 0;

        close(pipe1[1]); // close write end
        read(pipe1[0], &n, sizeof(n));
        read(pipe1[0], arr, sizeof(arr));
        read(pipe1[0], &key, sizeof(key));
        close(pipe1[0]);

        for (int i = 0; i < n; i++)
        {
            if (arr[i] == key)
            {
                found = 1;
                break;
            }
        }

        close(pipe2[0]); // close read end
        write(pipe2[1], &found, sizeof(found));
        close(pipe2[1]);
    }

    return 0;
}
