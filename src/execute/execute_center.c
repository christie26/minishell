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

// 이미 path가 붙은 상태로 들어온다. path 는 set 에서 붙여준다. 
void	ft_execute(char *cmd, char **options, char **env)
{
	if (ft_strncmp(cmd, "echo", 4))
		ft_echo(cmd, options, env);
	else if (ft_strncmp(cmd, "cd", 2))
		ft_cd(cmd, options, env);
	else if (ft_strncmp(cmd, "pwd", 3))
		ft_pwd(cmd, options, env);
	else if (ft_strncmp(cmd, "export", 6))
		ft_export(cmd, options, env);
	else if (ft_strncmp(cmd, "unset", 5))
		ft_unset(cmd, options, env);
	else if (ft_strncmp(cmd, "env", 6))
		ft_env(cmd, options, env);
	else if (ft_strncmp(cmd, "exit", 6))
		ft_exit(cmd, options, env);
	else
		execve(cmd, options, env);
}

void	close_center(t_process *process, int *p_fd, int read_end, int write_end)
{
	// close pipe
	close_fd(p_fd[READ], __FILE__, __LINE__);
	if (process->write_fd != 1)
		close_fd(p_fd[WRITE], __FILE__, __LINE__);
	
	// close read-end & write-end
	if (process->read_fd != 0)
		close_fd(read_end, __FILE__, __LINE__);
	if (process->write_fd == 2 | process->write_fd == 3)
		close_fd(write_end, __FILE__, __LINE__);
}

void	child_process(t_data *data, int *p_fd, int i, char **env)
{
	int	read_end;
	int	write_end;

	// set read_end
	if (data->process[i].read_fd == 0)
		read_end = STDIN_FILENO;
	else if (data->process[i].read_fd == 1)
		read_end = data->process[i - 1].pipe;
	else if (data->process[i].read_fd == 2)
		read_end = open(data->process[i].read_file, O_RDONLY);
	else
		read_end = open(data->process[i].read_file, O_RDONLY); // It has to be changed to heredoc options 

	// set write_end
	if (data->process[i].write_fd == 0)
		write_end = STDOUT_FILENO;
	else if (data->process[i].write_fd == 1)
	{
		write_end = p_fd[WRITE];
		data->process[i].pipe = p_fd[READ];
	}
	else if (data->process[i].write_fd == 2)
		write_end = open(data->process[i].write_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		write_end = open(data->process[i].write_file, O_CREAT | O_WRONLY | O_APPEND, 0644);

	duplicate_fd(read_end, write_end, __FILE__, __LINE__);
	close_center(&data->process[i], p_fd, read_end, write_end);
	ft_execute(data->process[i].cmd, data->process[i].options, env);
	exit(0);
}

void	parent_process(t_data *data, int *p_fd, int i, pid_t cpid)
{
	t_process	*process;

	process = &data->process[i];

	// close pipe fd
	if (process->write_fd == 1)
		process->pipe = p_fd[READ];
	else
		close_fd(p_fd[READ], __FILE__, __LINE__);
	close_fd((p_fd[WRITE]), __FILE__, __LINE__);

	// close prev_fd
	if (process->read_fd == 1)
		close_fd(data->process[i - 1].pipe, __FILE__, __LINE__);
	(void)(cpid);
	data->pid_set[i] = cpid;
}

int	execute_center(t_data *data, char **env)
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
	// printf("i = %d\n", i);
	i = data->number;
	while (i--)
		waitpid(data->pid_set[i], 0, 0);
	return (0);
}
