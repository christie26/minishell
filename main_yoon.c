#include "./include/mini_exec.h"

int main(int ac, char **av, char **env)
{
    mini_echo(av[1], 0);
}