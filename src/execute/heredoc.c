#include "./mini_exec.h"

void	child_heredoc(t_redirect *redirect, char **env, int p_fd[2])
{
	signal_setting_heredocmode();
	heredoc_open(redirect, env);
	ft_close(p_fd[0]);
	ft_close(p_fd[1]);
	exit(0);
}

int	parent_heredoc(int p_fd[2], pid_t cpid)
{
	int	exit_status;

	waitpid(cpid, &exit_status, 0);
	if (exit_status == 2)
		return (1);
	ft_close(p_fd[0]);
	ft_close(p_fd[1]);
	return (0);
}

int	run_heredoc(t_data *data, t_redirect *redirect)
{
	int			p_fd[2];
	pid_t		cpid;
	char		**env;

	env = data->my_env;
	if (pipe(p_fd) == -1)
		error_command("pipe");
	cpid = fork();
	if (cpid == -1)
		error_command("fork");
	if (cpid == 0)
		child_heredoc(redirect, env, p_fd);
	else
	{
		if (parent_heredoc(p_fd, cpid) == 1)
		{
			set_exit_status(data, 1);
			return (1);
		}
	}
	return (0);
}

int	heredoc_center(t_data *data, t_pipeline *pipeline)
{
	t_redirect	*redirect;

	while (pipeline)
	{
		redirect = pipeline->cmd_block->redirect;
		while (redirect)
		{
			if (redirect->type == 2)
			{
				if (run_heredoc(data, redirect))
					return (1);
			}
			redirect = redirect->next;
		}
		pipeline = pipeline->next;
	}
	return (0);
}
