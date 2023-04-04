
#include "./mini_exec.h"

int	get_process_number(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (pipeline)
	{
		pipeline = pipeline->next;
		i++;
	}
	return (i);
}


int	mini_execute(t_pipeline *pipeline, char **env)
{
	int		i;
	int		p_fd[2];
	t_data	data;
	pid_t	cpid;

	i = 0;
	data.process_number = get_process_number(pipeline);
	data.env = env;
	data.path = get_path(env);
	data.pid_set = malloc(sizeof(pid_t) * data.process_number);
	if (!data.pid_set)
		return (1);
	execute_center(&data, pipeline);
	
}
