#include <stdio.h>
#include <unistd.h>

int main()
{
    int p1[2], p2[2];
    pipe(p1); // parent -> child
    pipe(p2); // child -> parent

    int pid = fork();

    if (pid > 0)
    {
        // Parent Process
        int n, arr[100], key, result;

        printf("Enter size: ");
        scanf("%d", &n);

        printf("Enter elements: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        printf("Enter element to search: ");
        scanf("%d", &key);

        close(p1[0]); // close read end
        write(p1[1], &n, sizeof(n));
        write(p1[1], arr, sizeof(arr));
        write(p1[1], &key, sizeof(key));
        close(p1[1]);

        close(p2[1]); // close write end
        read(p2[0], &result, sizeof(result));

        if (result == 1)
            printf("Element Found\n");
        else
            printf("Element Not Found\n");

        close(p2[0]);
    }
    else
    {
        // Child Process
        int n, arr[100], key, found = 0;

        close(p1[1]); // close write end
        read(p1[0], &n, sizeof(n));
        read(p1[0], arr, sizeof(arr));
        read(p1[0], &key, sizeof(key));
        close(p1[0]);

        for (int i = 0; i < n; i++)
        {
            if (arr[i] == key)
            {
                found = 1;
                break;
            }
        }

        close(p2[0]); // close read end
        write(p2[1], &found, sizeof(found));
        close(p2[1]);
    }

    return 0;
}

