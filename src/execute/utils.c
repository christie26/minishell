
#include "./mini_exec.h"


void	ft_err_msg(int condition, char *error_message, char *file, int line)
{
	if (!condition)
		return ;
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(": error: ", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	ft_err_sys(int condition, char *file, int line)
{
	if (!condition)
		return ;
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	perror(": error");
	exit (EXIT_FAILURE);
}

void	close_fd(int fd, char *file, int line)
{
	int	ret;

	ret = close(fd);
	ft_err_sys(ret == -1, file, line);
}

// not using it 
void	duplicate_fd(int read_end, int write_end, char *file, int line)
{
	int	ret1;
	int	ret2;

	ret1 = dup2(read_end, STDIN_FILENO);
	ft_err_sys(ret1 == -1, file, line);
	ret2 = dup2(write_end, STDOUT_FILENO);
	ft_err_sys(ret2 == -1, file, line);
}
