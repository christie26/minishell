/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:36 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/04 14:17:28 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	while (*env++)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			break ;
	}
	path = ft_split((*env + 5), ':');
	ft_err_msg(!path, "Fail to malloc();", __FILE__, __LINE__);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		ft_err_msg(!path[i], "Fail to malloc();", __FILE__, __LINE__);
		free(tmp);
		i++;
	}
	return (path);
}

void	get_cmd(t_data *data, char **av)
{
	data->cmd_options[0] = ft_split(av[2], ' ');
	ft_err_msg(!data->cmd_options[0], "Fail to malloc();", __FILE__, __LINE__);
	data->cmd_options[1] = ft_split(av[3], ' ');
	ft_err_msg(!data->cmd_options[1], "Fail to malloc();", __FILE__, __LINE__);
	data->cmd[0] = data->cmd_options[0][0];
	data->cmd[1] = data->cmd_options[1][0];
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		ft_err_msg(!path_cmd, "Fail to malloc();", __FILE__, __LINE__);
		if (access(path_cmd, X_OK) == 0)
		{
			free(cmd);
			return (path_cmd);
		}
		free(path_cmd);
	i++;
	}
	return (0);
}

void	get_path_cmd(t_data *data, char **path)
{
	data->cmd[0] = check_access(data->cmd[0], path);
	ft_err_msg(!data->cmd[0], "Invalid command !", __FILE__, __LINE__);
	data->cmd_options[0][0] = data->cmd[0];
	data->cmd[1] = check_access(data->cmd[1], path);
	ft_err_msg(!data->cmd[1], "Invalid command !", __FILE__, __LINE__);
	data->cmd_options[1][0] = data->cmd[1];
}

int	pipex_set(char **av, char **env, t_data *data)
{
	char	**path;

	path = get_path(env);
	data->infile = av[1];
	data->outfile = av[4];
	get_cmd(data, av);
	get_path_cmd(data, path);
	free_array(path, 0);
	return (0);
}
