#include "./mini_exec.h"

int main(int ac, char **av, char **env)
{
	(void)(ac);
	(void)(ac);
	(void)(env);


	mini_echo(av[1], 0);
	return (0);
}
