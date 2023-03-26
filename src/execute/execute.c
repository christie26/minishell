/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:50:50 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 13:46:02 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

void	close_center(t_data *data, int *p_fd, int i)
{
	close_fd(p_fd[READ], __FILE__, __LINE__);
	close_fd(p_fd[WRITE], __FILE__, __LINE__);
	if (i != 0)
		close_fd(data->read_fd, __FILE__, __LINE__);
}

void	child_process(t_data *data, int *p_fd, int i, char **env)
{
	int	infile;
	int	outfile;

	if (i == 0)
	{
		infile = open(data->infile, O_RDONLY);
		ft_err_sys(infile == -1, __FILE__, __LINE__);
		duplicate_fd(infile, p_fd[WRITE], __FILE__, __LINE__);
		close_fd(infile, __FILE__, __LINE__);
	}
	else if (i == data->number - 1)
	{
		if (data->offset == 3)
			outfile = open(data->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			outfile = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_err_sys(outfile == -1, __FILE__, __LINE__);
		duplicate_fd(data->read_fd, outfile, __FILE__, __LINE__);
		close_fd(outfile, __FILE__, __LINE__);
	}
	else
		duplicate_fd(data->read_fd, p_fd[WRITE], __FILE__, __LINE__);
	close_center(data, p_fd, i);
	execve(data->cmd[i], data->cmd_options[i], env);
	exit(0);
}

void	parent_process(t_data *data, int *p_fd, int i, pid_t cpid)
{
	if (i == 0)
		data->read_fd = p_fd[READ];
	else if (i == data->number - 1)
	{
		close_fd(data->read_fd, __FILE__, __LINE__);
		close_fd(p_fd[READ], __FILE__, __LINE__);
	}
	else
	{
		close_fd(data->read_fd, __FILE__, __LINE__);
		data->read_fd = p_fd[READ];
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
	while (i < data->number)
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
	i = data->number;
	while (i--)
		waitpid(data->pid_set[i], 0, 0);
	return (0);
}
