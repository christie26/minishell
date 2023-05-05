/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:50:21 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 20:30:56 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

void	ft_execute(char **options, t_data *data)
{
	char	*cmd;
	char	*cmd_path;

	cmd = options[0];
	if (!cmd)
		exit(0);
	if (is_builtin(cmd))
		exit(ft_builtin(options, data));
	if (is_exist(cmd))
		cmd_path = cmd;
	else
	{
		cmd_path = check_access(cmd, data->path);
		if (!cmd_path)
		{
			g_exit_status = 127;
			error_command_msg(cmd, CMD_ERROR);
			return ;
		}
	}
	if (is_directory(cmd_path))
	{
		error_command_msg(cmd, DIREC_ERROR);
		exit(126);
	}
	if (execve(cmd_path, options, get_env(data->my_env)) == -1)
	{
		error_command(cmd);
		exit(126);
	}
}

void	child_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i)
{
	g_exit_status = 0;
	signal_setting_commandmode();
	if (i != 0)
	{
		ft_dup2(data->prev_fd, 0);
		ft_close(data->prev_fd);
	}
	if (i != data->process_number - 1)
	{
		ft_dup2(p_fd[1], 1);
		data->prev_fd = p_fd[0];
	}
	if (redirection_center(pipeline->cmd_block->redirect))
		g_exit_status = 1;
	ft_close(p_fd[0]);
	ft_close(p_fd[1]);
	if (g_exit_status == 0)
		ft_execute(pipeline->cmd_block->cmd, data);
	exit(g_exit_status);
}

void	parent_process(t_data *data, int *p_fd, int i, pid_t cpid)
{
	if (i == 0)
		data->prev_fd = p_fd[0];
	else if (i == data->process_number - 1)
	{
		ft_close(data->prev_fd);
		ft_close(p_fd[READ]);
	}
	else
	{
		ft_close(data->prev_fd);
		data->prev_fd = p_fd[READ];
	}
	ft_close((p_fd[WRITE]));
	data->pid_set[i] = cpid;
}
