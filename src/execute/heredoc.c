/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:50:39 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:50:39 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

void	child_heredoc(char *delimeter, char **env, int p_fd[2], char *new_file)
{
	int	fd;

	signal_setting_heredocmode();
	fd = open(new_file, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		error_command("heredoc");
	heredoc_write(fd, delimeter, env);
	ft_close(p_fd[0]);
	ft_close(p_fd[1]);
	exit(0);
}

void	parent_heredoc(int p_fd[2], pid_t cpid)
{
	int	exit_status;

	waitpid(cpid, &exit_status, 0);
	if (exit_status == 2)
		g_exit_status = 1;
	ft_close(p_fd[0]);
	ft_close(p_fd[1]);
}

int	run_heredoc(t_data *data, t_redirect *redirect)
{
	int			p_fd[2];
	pid_t		cpid;
	char		**env;
	char		*new_file;
	char		*delimeter;

	env = data->my_env;
	delimeter = redirect->filename;
	if (pipe(p_fd) == -1)
		error_command("pipe");
	cpid = fork();
	if (cpid == -1)
		error_command("fork");
	new_file = get_tmp_file();
	if (cpid == 0)
		child_heredoc(delimeter, env, p_fd, new_file);
	else
		parent_heredoc(p_fd, cpid);
	free(redirect->filename);
	redirect->filename = new_file;
	return (0);
}

int	heredoc_center(t_data *data, t_pipeline *pipeline)
{
	t_redirect	*redirect;

	while (pipeline)
	{
		redirect = pipeline->cmd_block->redirect;
		while (redirect)
		{
			if (redirect->type == 2)
			{
				run_heredoc(data, redirect);
				if (g_exit_status == 1)
					return (1);
			}
			redirect = redirect->next;
		}
		pipeline = pipeline->next;
	}
	return (0);
}
