/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:51:03 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 20:30:47 by yoonsele         ###   ########.fr       */
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
	int		exit_status;
	pid_t	cpid;

	i = -1;
	while (++i < data->process_number)
	{
		if (pipe(p_fd) == -1)
			error_command("pipe");
		cpid = fork();
		if (cpid == -1)
			error_command("fork");
		if (cpid == 0)
			child_process(data, pipeline, p_fd, i);
		else
			parent_process(data, p_fd, i, cpid);
		pipeline = pipeline->next;
	}
	i = -1;
	while (++i < data->process_number)
		waitpid(data->pid_set[i], &exit_status, 0);
	get_short_exit(exit_status);
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

int	mini_execute(t_pipeline *pipeline, t_data *data)
{
	int	return_value;

	return_value = 0;
	data->process_number = get_process_number(pipeline);
	if (data->process_number > 1024)
	{
		error_command_msg("dup2", PIPE_ERROR);
		exit (24);
	}
	data->path = set_path(data->my_env);
	data->pid_set = malloc(sizeof(pid_t) * data->process_number);
	if (!data->pid_set)
		exit(EXIT_FAILURE);
	if (heredoc_center(data, pipeline))
		return (1);
	if (data->process_number == 1 && is_builtin(pipeline->cmd_block->cmd[0]))
		only_builtin(data, pipeline);
	else
		execute_center(data, pipeline);
	heredoc_unlink(pipeline);
	free_path(data->path);
	free(data->pid_set);
	return (return_value);
}
