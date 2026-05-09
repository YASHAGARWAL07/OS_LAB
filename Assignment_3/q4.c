#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void scan_char(int d, char *c)
{
    char buf[10];
    read(0, buf, 10);
    *c = buf[0];
}

void scan_int(int d, int *x)
{
    char buf[20];
    read(0, buf, 20);
    *x = atoi(buf);
}

void scan_float(int d, float *y)
{
    char buf[20];
    read(0, buf, 20);
    *y = atof(buf);
}

int main()
{
    char c;
    int i;
    float f;

    printf("Enter character: ");
    scan_char(1,&c);

    printf("Enter integer: ");
    scan_int(2,&i);

    printf("Enter float: ");
    scan_float(3,&f);

    printf("\nCharacter = %c\n",c);
    printf("Integer = %d\n",i);
    printf("Float = %f\n",f);

    return 0;
}
