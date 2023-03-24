/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:50:50 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 12:32:01 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	child_process(t_data *data, int p_fd[], int i, char **env)
{
	int	infile;
	int	outfile;

	if (i == 0)
	{
		infile = open(data->infile, O_RDONLY);
		ft_err_sys(infile == -1, __FILE__, __LINE__);
		duplicate_fd(infile, p_fd[WRITE], __FILE__, __LINE__);
	}
	else
	{
		outfile = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_err_sys(outfile == -1, __FILE__, __LINE__);
		duplicate_fd(data->read_fd, outfile, __FILE__, __LINE__);
		close_fd(outfile, __FILE__, __LINE__);
		close_fd(data->read_fd, __FILE__, __LINE__);
	}
	close_fd(p_fd[READ], __FILE__, __LINE__);
	close_fd(p_fd[WRITE], __FILE__, __LINE__);
	execve(data->cmd[i], data->cmd_options[i], env);
	exit(0);
}

void	parent_process(t_data *data, int p_fd[], int i, pid_t cpid)
{
	if (i == 0)
		data->read_fd = p_fd[READ];
	else
	{
		close_fd(data->read_fd, __FILE__, __LINE__);
		close_fd(p_fd[READ], __FILE__, __LINE__);
	}
	close_fd((p_fd[WRITE]), __FILE__, __LINE__);
	data->pid_set[i] = cpid;
}

int	pipex_execute(t_data *data, char **env)
{
	int		i;
	int		p_fd[2];
	pid_t	cpid;

	i = 0;
	while (i < 2)
	{
		ft_err_sys(pipe(p_fd) == -1, __FILE__, __LINE__);
		cpid = fork();
		ft_err_sys(cpid == -1, __FILE__, __LINE__);
		if (cpid == 0)
			child_process(data, p_fd, i, env);
		else
			parent_process(data, p_fd, i, cpid);
		i++;
	}
	waitpid(data->pid_set[0], 0, 0);
	waitpid(data->pid_set[1], 0, 0);
	return (0);
}
