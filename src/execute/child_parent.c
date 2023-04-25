#include "./mini_exec.h"

void	ft_execute(char **options, t_data *data)
{
	char	*cmd;

	cmd = options[0];
	if (is_builtin(cmd))
		exit(ft_builtin(options, data));
	else
	{
		cmd = check_access(cmd, data->path);
		if (!cmd)
		{
			short_exit_status = 127;
			ft_err_msg_exit(1, CMD_ERROR, __FILE__, __LINE__);
		}
		if (execve(cmd, options, get_env(data->my_env)) == -1)
			ft_err_sys_exit(1, __FILE__, __LINE__);
	}
}

void	child_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i)
{
	if (i != 0)
	{
		if (dup2(data->prev_fd, 0) == -1)
			ft_err_sys_exit(1, __FILE__, __LINE__);
		ft_close(data->prev_fd, __FILE__, __LINE__);
	}
	if (i != data->process_number - 1)
	{
		if (dup2(p_fd[1], 1) == -1)
			ft_err_sys_exit(1, __FILE__, __LINE__);
		data->prev_fd = p_fd[0];
	}
	if (!redirection_center(pipeline->cmd_block->redirect))
	{
		ft_close(p_fd[0], __FILE__, __LINE__);
		ft_close(p_fd[1], __FILE__, __LINE__);
		ft_execute(pipeline->cmd_block->cmd, data);
	}
	else
		short_exit_status = 1;
	exit(short_exit_status);
}

void	parent_process(t_data *data, int *p_fd, int i, pid_t cpid)
{
	if (i == 0)
		data->prev_fd = p_fd[0];
	else if (i == data->process_number - 1)
	{
		ft_close(data->prev_fd, __FILE__, __LINE__);
		ft_close(p_fd[READ], __FILE__, __LINE__);
	}
	else
	{
		ft_close(data->prev_fd, __FILE__, __LINE__);
		data->prev_fd = p_fd[READ];
	}
	ft_close((p_fd[WRITE]), __FILE__, __LINE__);
	data->pid_set[i] = cpid;
}
