#include "./mini_exec.h"

void	redirection_1(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (dup2(fd, 0) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (close(fd) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
}

void	redirection_2(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (dup2(fd, 0) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (close(fd) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
}

void	redirection_3(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (dup2(fd, 1) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (close(fd) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
}

void	redirection_4(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (dup2(fd, 1) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
	if (close(fd) == -1)
		ft_err_sys_exit(1, __FILE__, __LINE__);
}

void	redirection_center(t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == 1)
			redirection_1(redirect->filename);
		else if (redirect->type == 2)
			redirection_2(redirect->filename);
		else if (redirect->type == 3)
			redirection_3(redirect->filename);
		else
			redirection_4(redirect->filename);
		redirect = redirect->next;
	}
}
