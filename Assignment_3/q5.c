#include<stdio.h>
#include<unistd.h>
#include<string.h>

void print_char(char c)
{
    write(1, &c, 1);
}

void print_int(int x)
{
    char buf[20];
    sprintf(buf,"%d",x);
    write(1, buf, strlen(buf));
}

void print_float(float f)
{
    char buf[20];
    sprintf(buf,"%f",f);
    write(1, buf, strlen(buf));
}

int main()
{
    char c='A';
    int i=25;
    float f=3.14;

    write(1,"Character = ",12);
    print_char(c);

    write(1,"\nInteger = ",11);
    print_int(i);

    write(1,"\nFloat = ",9);
    print_float(f);

    write(1,"\n",1);

    return 0;
}

