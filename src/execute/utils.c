#include "./mini_exec.h"

void	ft_close(int fd, char *file, int line)
{
	int	ret;

	ret = close(fd);
	ft_err_sys_exit(ret == -1, file, line);
}
