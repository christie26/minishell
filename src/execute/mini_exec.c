/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:51:03 by yoonsele          #+#    #+#             */
/*   Updated: 2023/06/22 18:23:23 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

int	get_process_number(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (pipeline)
	{
		pipeline = pipeline->next;
		i++;
	}
	return (i);
}

void	execute_center(t_data *data, t_pipeline *pipeline)
{
	int		i;
	int		p_fd[2];
	pid_t	cpid;

	i = -1;
	ft_memset(p_fd, 0, 2 * sizeof(int));
	while (++i < data->process_number)
	{
		if (data->process_number > 1)
			if (pipe(p_fd) == -1)
				error_command("pipe");
		cpid = fork();
		if (cpid == -1)
			error_command("fork");
		if (cpid == 0)
			child_process(data, pipeline, p_fd, i);
		else
			parent_process(data, p_fd, i);
		pipeline = pipeline->next;
	}
	update_exit(data->process_number, cpid);
}

void	only_builtin(t_data *data, t_pipeline *pipeline)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (redirection_center(pipeline->cmd_block->redirect))
		g_exit_status = 1;
	else
		g_exit_status = ft_builtin(pipeline->cmd_block->cmd, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
}

void	mini_execute(t_pipeline *pipeline, t_data *data)
{
	data->process_number = get_process_number(pipeline);
	if (data->process_number > 1024)
	{
		error_command_msg("dup2", PIPE_ERROR);
		exit (24);
	}
	data->path = set_path(data->my_env);
	if (heredoc_center(data, pipeline))
		return ;
	if (data->process_number == 1 && is_builtin(pipeline->cmd_block->cmd[0]))
		only_builtin(data, pipeline);
	else
		execute_center(data, pipeline);
	return ;
}
