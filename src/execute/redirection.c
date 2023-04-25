#include "./mini_exec.h"

int	redirection_1(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (dup2(fd, 0) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (close(fd) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	return (0);
}

int	redirection_2(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (dup2(fd, 0) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (close(fd) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	return (0);
}

int	redirection_3(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (dup2(fd, 1) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (close(fd) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	return (0);
}

int	redirection_4(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (dup2(fd, 1) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	if (close(fd) == -1)
		return (ft_err_sys(1, __FILE__, __LINE__));
	return (0);
}

int	redirection_center(t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == 1)
		{
			if (redirection_1(redirect->filename))
				return (1);
		}
		else if (redirect->type == 2)
		{
			if (redirection_2(redirect->filename))
				return (1);
		}
		else if (redirect->type == 3)
		{
			if (redirection_3(redirect->filename))
				return (1);
		}
		else
		{
			if (redirection_4(redirect->filename))
				return (1);
		}
		redirect = redirect->next;
	}
	return (0);
}
