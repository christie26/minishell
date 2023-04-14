
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

int	execute_center(t_data *data, t_pipeline *pipeline)
{
	int		i;
	int		p_fd[2];
	pid_t	cpid;

	i = 0;
	while (i < data->process_number)
	{
		if (is_builtin(pipeline->cmd_block->cmd[0]))
		{
			printf("it's built-in\n");
			if (ft_builtin(pipeline, data->env))
			{
				ft_err_msg(1, "Error", __FILE__, __LINE__);	// have to think more 
			// have to think about pipe and redirection stuff
			}
			i++;
			continue ;
		}
		ft_err_sys(pipe(p_fd) == -1, __FILE__, __LINE__);
		cpid = fork();
		ft_err_sys(cpid == -1, __FILE__, __LINE__);
		if (cpid == 0)
			child_process(data, pipeline, p_fd, i);
		else
			parent_process(data, pipeline, p_fd, i, cpid);
		i++;
		pipeline = pipeline->next;
	}

	while (i--)
		waitpid(data->pid_set[i], 0, 0);
	return (0);
}

int	mini_execute(t_pipeline *pipeline, char **env)
{
	// int		i;
	t_data	data;

	// i = 0;
	data.process_number = get_process_number(pipeline);
	data.env = env;
	data.path = get_path(env);
	data.pid_set = malloc(sizeof(pid_t) * data.process_number);
	if (!data.pid_set)
		return (1);
	execute_center(&data, pipeline);
	return (0);
}
