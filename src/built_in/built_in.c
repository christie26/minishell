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

int ft_echo(char *cmd, char **options, char **env)
{
	int	endl;

	options++;
	endl = 1;
	if (!ft_strcmp(*options, "-n"))	// in case of option -n, it has to be the first 
	{
		options++;
		endl = 0;
	}
	while (*options)
	{
		ft_putstr_fd(*options, 1);
		options++;
		if (*options)
			ft_putchar_fd(' ', 1);
	}
	if (endl)
		ft_putchar_fd('\n', 1);
    (void)(cmd);
    (void)(env);
	return (0);
}

int ft_cd(char *cmd, char **options, char **env)
{
    printf("execute cd\n");
    (void)(cmd);
    (void)(options);
    (void)(env);
	return (0);
}

int ft_pwd(char *cmd, char **options, char **env)
{
    printf("execute pwd\n");    
    (void)(cmd);
    (void)(options);
    (void)(env);
	return (0);
}

int ft_export(char *cmd, char **options, char **env)
{
    printf("execute export\n");
    (void)(cmd);
    (void)(options);
    (void)(env);
	return (0);
}

int ft_unset(char *cmd, char **options, char **env)
{
    printf("execute unset\n");
    (void)(cmd);
    (void)(options);
    (void)(env);
	return (0);
}

int ft_env(char *cmd, char **options, char **env)
{
    printf("execute env\n");
    (void)(cmd);
    (void)(options);
    (void)(env);
	return (0);
}

int ft_exit(char *cmd, char **options, char **env)
{
    printf("execute exit\n");
    (void)(cmd);
    (void)(options);
    (void)(env);
	return (0);
}

#include <string.h>
// run builtin here
// return 0 if it sucess, return 1 if there's a error 
int ft_builtin(t_pipeline *pipeline, char **env)
{
	char	*cmd;
	char	**options;

	cmd = pipeline->cmd_block->cmd[0];
	options = pipeline->cmd_block->cmd;

	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(cmd, options, env));
	else if (!ft_strcmp(cmd, "cd")) 
		return (ft_cd(cmd, options, env));
	else if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd(cmd, options, env));
	else if (!ft_strcmp(cmd, "export"))
		return (ft_export(cmd, options, env));
	else if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(cmd, options, env));
	else if (!ft_strcmp(cmd, "env"))
		return (ft_env(cmd, options, env));
	else if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(cmd, options, env));
	else
		return (0);
}

// check cmd if it's builtin cmd or not 
int is_builtin(char	*cmd)
{
	if (!strcmp(cmd, "echo"))
		return (1);
	else if (!strcmp(cmd, "cd"))
		return (1);
	else if (!strcmp(cmd, "pwd"))
		return (1);
	else if (!strcmp(cmd, "export"))
		return (1);
	else if (!strcmp(cmd, "unset"))
		return (1);
	else if (!strcmp(cmd, "env"))
		return (1);
	else if (!strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}