#include "../include/mini_exec.h"
#include <stdio.h>

int mini_echo(char *file, int option)
{
    if (option)
    {
        printf("I want to execute echo with option\n");
        printf("parameter is %s\n", file);
    }
    else   
    {
        printf("I want to execute echo without option\n");
        printf("parameter is %s\n", file);
    }
}