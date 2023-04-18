/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:47:00 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/24 21:49:19 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./built_in.h"

int	ft_builtin(char	**argv, t_data *data)
{
	char	*cmd;
	char	**env;

	cmd = argv[0];
	env = data->my_env;
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(cmd, argv, env));
	else if (!ft_strcmp(cmd, "cd"))
		return (ft_cd(cmd, argv, env));
	else if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd(cmd, argv, env));
	else if (!ft_strcmp(cmd, "export"))
		return (ft_export(argv, data));
	else if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(cmd, argv, env));
	else if (!ft_strcmp(cmd, "env"))
		return (ft_env(cmd, argv, env));
	else if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(cmd, argv, env));
	else
		return (0);
}

int	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}
