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

int	cmd_valid_check(t_pipeline *pipeline, t_data *data)
{
	int 	i;
	char	*cmd;

	i = 0;
	while (i < data->process_number)
	{
		cmd = pipeline->cmd_block->cmd[0];
		if (is_builtin(cmd))
		{
			i++;
			pipeline = pipeline->next;
			continue ;
		}
		cmd = check_access(cmd, data->path);
		if (!cmd)
		{
			ft_err_msg(1, CMD_ERROR, __FILE__, __LINE__);
			short_exit_status = 127;
			return (1);
		}
		pipeline->cmd_block->cmd[0] = cmd;
		i++;
		pipeline = pipeline->next;
	}
	return (0);		
}

void	execute_center(t_data *data, t_pipeline *pipeline)
{
	int		i;
	int		p_fd[2];
	int		exit_status;
	pid_t	cpid;

	i = -1;
	// if (cmd_valid_check(pipeline, data))
		// return ;
	while (++i < data->process_number)
	{
		ft_err_sys(pipe(p_fd) == -1, __FILE__, __LINE__);
		cpid = fork();
		ft_err_sys(cpid == -1, __FILE__, __LINE__);
		if (cpid == 0)
			child_process(data, pipeline, p_fd, i);
		else
			parent_process(data, p_fd, i, cpid);
		if (short_exit_status == 127)
			return ;
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
	{
		int saved_stdin = dup(STDIN_FILENO);
		int saved_stdout = dup(STDOUT_FILENO);
		redirection_center(pipeline->cmd_block->redirect);
		set_exit_status(data, ft_builtin(pipeline->cmd_block->cmd, data));
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
	}
	else
		execute_center(data, pipeline);
	heredoc_unlink(pipeline);
	return (0);
}
