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

void	ft_close(int fd, char *file, int line)
{
	int	ret;

	ret = close(fd);
	ft_err_sys_exit(ret == -1, file, line);
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
	free(key_value);
}
