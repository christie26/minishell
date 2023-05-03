#include "./mini_exec.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_close(int fd)
{
	int	result;

	result = close(fd);
	if (result == -1)
	{
		error_command("close");
		exit (EXIT_FAILURE);
	}
}

void	ft_dup2(int fd_from, int fd_to)
{
	int	result;

	result = dup2(fd_from, fd_to);
	if (result == -1)
	{
		error_command("dup2");
		exit (EXIT_FAILURE);
	}
}

void	get_short_exit(int exit_status)
{
	if (exit_status == 2 || exit_status == 3)
	{
		g_exit_status = 128 + exit_status;
		return ;
	}
	if (WIFEXITED(exit_status))
		g_exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		g_exit_status = WTERMSIG(exit_status);
	else
		g_exit_status = WSTOPSIG(exit_status);
}

void	set_exit_status(t_data *data, int g_exit_status)
{
	char	*value;
	char	*key_value;

	value = ft_itoa(g_exit_status);
	if (!value)
		exit(EXIT_FAILURE);
	key_value = ft_strjoin("?=", value);
	if (!key_value)
		exit(EXIT_FAILURE);
	free(value);
	add_variable(key_value, data);
	free(key_value);
}
