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

int	get_short_exit(int exit_status)
{
	if (WIFEXITED(exit_status))
		short_exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		short_exit_status = WTERMSIG(exit_status);
	else
		short_exit_status = WSTOPSIG(exit_status);
	return (short_exit_status);
}

void	set_exit_status(t_data *data, int short_exit_status)
{
	char	*value;
	char	*key_value;

	value = ft_itoa(short_exit_status);
	ft_err_msg_exit(!value, MALLOC_ERROR, __FILE__, __LINE__);
	key_value = ft_strjoin("?=", value);
	free(value);
	ft_err_msg_exit(!key_value, MALLOC_ERROR, __FILE__, __LINE__);
	add_variable(key_value, data);
}

void	execute_center(t_data *data, t_pipeline *pipeline)
{
	int		i;
	int		p_fd[2];
	int		exit_status;
	pid_t	cpid;

	i = -1;
	while (++i < data->process_number)
	{
		ft_err_sys(pipe(p_fd) == -1, __FILE__, __LINE__);
		cpid = fork();
		ft_err_sys(cpid == -1, __FILE__, __LINE__);
		if (cpid == 0)
			child_process(data, pipeline, p_fd, i);
		else
			parent_process(data, p_fd, i, cpid);
		pipeline = pipeline->next;
	}
	i = -1;
	while (++i < data->process_number)
		waitpid(data->pid_set[i], &exit_status, 0);
	get_short_exit(exit_status);
	set_exit_status(data, short_exit_status);
}

int	mini_execute(t_pipeline *pipeline, t_data *data)
{
	data->process_number = get_process_number(pipeline);
	data->path = get_path(data->my_env);
	data->pid_set = malloc(sizeof(pid_t) * data->process_number);
	ft_err_msg_exit(!data->pid_set, MALLOC_ERROR, __FILE__, __LINE__);
	heredoc_center(pipeline);
	if (data->process_number == 1 && is_builtin(pipeline->cmd_block->cmd[0]))
		set_exit_status(data, ft_builtin(pipeline->cmd_block->cmd, data));
	else
		execute_center(data, pipeline);
	heredoc_unlink(pipeline);
	return (0);
}
