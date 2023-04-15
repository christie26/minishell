#include <stdio.h>

int main()
{
    int *p = 0;

    printf("Hello I wil crash!!\n");

    *p = 3;
    return 0;
}