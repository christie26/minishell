/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:50:31 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:50:32 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (exit_status == 3)
			write(1, "Quit: 3\n", 8);
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
