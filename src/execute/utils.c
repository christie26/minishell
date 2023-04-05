
#include "./mini_exec.h"

void	close_fd(int fd, char *file, int line)
{
	int	ret;

	ret = close(fd);
	ft_err_sys(ret == -1, file, line);
}

// not using it 
// void	duplicate_fd(int read_end, int write_end, char *file, int line)
// {
// 	int	ret1;
// 	int	ret2;

// 	ret1 = dup2(read_end, STDIN_FILENO);
// 	ft_err_sys(ret1 == -1, file, line);
// 	ret2 = dup2(write_end, STDOUT_FILENO);
// 	ft_err_sys(ret2 == -1, file, line);
// }
