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

char	*child_heredoc(t_redirect *redirect, char **env, int p_fd[2])
{
	char *new_file;

	signal_setting_heredocmode();
	new_file = heredoc_open(redirect, env);
	ft_close(p_fd[0]);
	ft_close(p_fd[1]);
	return (new_file);
}

int	parent_heredoc(int p_fd[2], pid_t cpid)
{
	int	exit_status;

	waitpid(cpid, &exit_status, 0);
	if (exit_status == 2)
		return (1);
	ft_close(p_fd[0]);
	ft_close(p_fd[1]);
	return (0);
}

int	run_heredoc(t_data *data, t_redirect *redirect)
{
	int			p_fd[2];
	pid_t		cpid;
	char		**env;
	char		*new_file;

	env = data->my_env;
	if (pipe(p_fd) == -1)
		error_command("pipe");
	cpid = fork();
	if (cpid == -1)
		error_command("fork");
	new_file = 0;
	if (cpid == 0)
	{
		new_file = child_heredoc(redirect, env, p_fd);
		exit(0);
	}
	else
	{
		if (parent_heredoc(p_fd, cpid) == 1)
		{
			g_exit_status = 1;
			return (1);
		}
	}
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
				if (run_heredoc(data, redirect))
					return (1);
			}
			redirect = redirect->next;
		}
		pipeline = pipeline->next;
	}
	return (0);
}
