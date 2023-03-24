/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:25 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 13:42:46 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

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

void	duplicate_fd(int read_end, int write_end, char *file, int line)
{
	int	ret1;
	int	ret2;

	ret1 = dup2(read_end, STDIN_FILENO);
	ft_err_sys(ret1 == -1, file, line);
	ret2 = dup2(write_end, STDOUT_FILENO);
	ft_err_sys(ret2 == -1, file, line);
}

void	free_array(char **item, int i)
{
	while (item[i])
	{
		free(item[i]);
		i++;
	}
	free(item);
}
