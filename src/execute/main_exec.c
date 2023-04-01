#include "./mini_exec.h"

int main(int ac, char **av, char **env)
{
	t_process	*process;
	t_data		data;

	process = malloc(sizeof(t_process) * 3);

	process[0].order = 0; 
	process[0].read_fd = 0; 
	process[0].read_file = 0; 
	process[0].write_fd = 1; 
	process[0].write_file = 0; 
	process[0].cmd = "cat"; 
	process[0].options = 0; 

	process[1].order = 1; 
	process[1].read_fd = 1; 
	process[1].read_file = 0; 
	process[1].write_fd = 2; 
	process[1].write_file = "outfile"; 
	process[1].cmd = "grep"; 
	process[1].options = ft_split("gerp a", ' '); 

	data.number = 3;
	data.process = process;
	data.pid_set = malloc(sizeof(pid_t) * data.number);

	execute_center(&data, env);

	(void)(ac);
	(void)(av);


	// mini_echo(av[1], 0);

	return (0);
}
