#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    pid_t id = fork();
    printf("hello from id : %d\n", id);
    if( id == 0)
    {
        printf("I am the child bro\n");
    }
    if( id > 0)
    {
        printf("I am the parent process\n");
    }
}