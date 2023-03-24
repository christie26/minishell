/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:46 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 14:18:59 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	malloc_center(t_data *data)
{
	data->cmd = (char **)malloc(sizeof(char *) * data->number);
	ft_err_msg(!data->cmd, "Fail to malloc();", __FILE__, __LINE__);
	data->cmd_options = (char ***)malloc(sizeof(char **) * data->number);
	ft_err_msg(!data->cmd_options, "Fail to malloc();", __FILE__, __LINE__);
	data->pid_set = (pid_t *)malloc(sizeof(pid_t) * data->number);
	ft_err_msg(!data->pid_set, "Fail to malloc();", __FILE__, __LINE__);
}

void	free_center(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		free(data->cmd[i]);
		free_array(data->cmd_options[i], 1);
		i++;
	}
	free(data->cmd);
	free(data->cmd_options);
	free(data->pid_set);
	if (data->offset == 3)
	{
		ft_err_sys(unlink(data->infile) == -1, __FILE__, __LINE__);
		free(data->infile);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		ft_err_msg(ac < 6, "Invalid number of arguments", __FILE__, __LINE__);
		data.limiter = av[2];
		data.number = ac - 4;
		data.offset = 3;
	}
	else
	{
		ft_err_msg(ac < 5, "Invalid number of arguments", __FILE__, __LINE__);
		(void)(data.limiter);
		data.number = ac - 3;
		data.offset = 2;
	}
	malloc_center(&data);
	pipex_set(av, env, &data);
	pipex_execute(&data, env);
	free_center(&data);
	return (EXIT_SUCCESS);
}
