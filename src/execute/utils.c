#include "./mini_exec.h"

void	ft_close(int fd, char *file, int line)
{
	int	ret;

	ret = close(fd);
	ft_err_sys(ret == -1, file, line);
}
