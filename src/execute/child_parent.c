
#include "./mini_exec.h"

void	ft_execute(char **options, t_data *data)
{
	char	*cmd;
	char	**env;

	env = data->env;
	cmd = ft_strdup(options[0]);
	cmd = check_access(cmd, data->path); // leak check 
	ft_err_msg(!cmd, "Invalid command !", __FILE__, __LINE__);
	execve(cmd, options, env);
}

void	child_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i)
{
	// set pipe
	// connect this process with previous process with prev_fd
	if (i != 0)
	{
		dup2(data->prev_fd, 0);
		dup2(p_fd[1], 1);
		data->prev_fd = p_fd[0];	// Is it right place? 
	}	

	// set redirection
	t_redirect *redirect;
	int	read_end;
	int	write_end;

	redirect = pipeline->cmd_block->redirect;
	while (redirect)
	{
		if (redirect->type == 1)
		{
			read_end = open(redirect->filename, O_RDONLY);
			dup2(read_end, 0);
			close_fd(read_end, __FILE__, __LINE__);
		}
		else if (redirect->type == 2)
		{
			read_end = open(redirect->filename, O_RDONLY); // here_doc
			dup2(read_end, 0);
			close_fd(read_end, __FILE__, __LINE__);
		}
		else if (redirect->type == 3)
		{
			write_end = open(redirect->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(write_end, 1);
			close_fd(write_end, __FILE__, __LINE__);
		}
		else
		{
			write_end = open(redirect->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(write_end, 1);
			close_fd(write_end, __FILE__, __LINE__);
		}
		redirect = redirect->next;
	}
	close_fd(p_fd[0], __FILE__, __LINE__);
	close_fd(p_fd[1], __FILE__, __LINE__);

	// execute
	ft_execute(pipeline->cmd_block->cmd, data);
	exit(0);
}

void	parent_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i, pid_t cpid)
{
	if (i == 0)
	{
		close_fd(p_fd[1], __FILE__, __LINE__);
		data->prev_fd = p_fd[0];
	}
	else if (i == data->process_number - 1)
	{
		close_fd(p_fd[1], __FILE__, __LINE__);
		close_fd(data->prev_fd, __FILE__, __LINE__);
		data->prev_fd = p_fd[0];
	}
	else
	{
		close_fd(p_fd[0], __FILE__, __LINE__);
		close_fd(p_fd[1], __FILE__, __LINE__);
	}
	data->pid_set[i] = cpid;
}