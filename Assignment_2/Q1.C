#include <stdio.h>

int main(int arg, char *args[])
{
    if(arg < 3)
    {
        printf("Error: Less than 3 arguments are passed\n");
        return 0;
    }
    else
    {
        printf("Arguments entered are:\n");

        for(int i = 1; i < arg; i++)
        {
            printf("The %d argument is %s\n", i, args[i]);
        }
    }

    return 0;
}
