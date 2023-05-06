/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:50:35 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 19:19:04 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

char	**get_path(char **env)
{
	char	**path;

	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			break ;
		env++;
	}
	if (*env == NULL)
		return (0);
	path = ft_split((*env + 5), ':');
	if (!path)
		exit(EXIT_FAILURE);
	return (path);
}

char	**set_path(char **env)
{
	int		i;
	char	*tmp;
	char	**path;

	path = get_path(env);
	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
			exit(EXIT_FAILURE);
		free(tmp);
		i++;
	}
	return (path);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	if (ft_strlen(cmd) == 0 || !path)
		return (0);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		if (!path_cmd)
			exit(EXIT_FAILURE);
		if (is_exist(path_cmd))
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (0);
}

char	*get_cmd_path(char *cmd, char **path)
{
	if (is_exist(cmd))
		return (cmd);
	else
		return (check_access(cmd, path));
}
