
#include "../includes/libft.h"

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