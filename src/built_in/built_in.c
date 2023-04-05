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

#include "./mini_exec.h"

int ft_echo(char *cmd, char **options, char **env)
{
    printf("execute echo\n");
    (void)(cmd);
    (void)(options);
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

// run builtin here
// return 0 if it sucess, return 1 if there's a error 
int ft_builtin(t_pipeline *pipeline, char **env)
{
	char	*cmd;
	char	**options;

	cmd = pipeline->cmd_block->cmd[0];
	options = pipeline->cmd_block->cmd;

	if (ft_strncmp(cmd, "echo", 4))
		return (ft_echo(cmd, options, env));
	else if (ft_strncmp(cmd, "cd", 2))
		return (ft_cd(cmd, options, env));
	else if (ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd(cmd, options, env));
	else if (ft_strncmp(cmd, "export", 6))
		return (ft_export(cmd, options, env));
	else if (ft_strncmp(cmd, "unset", 5))
		return (ft_unset(cmd, options, env));
	else if (ft_strncmp(cmd, "env", 6))
		return (ft_env(cmd, options, env));
	else if (ft_strncmp(cmd, "exit", 6))
		return (ft_exit(cmd, options, env));
	else
		return (0);
}

// check cmd if it's builtin cmd or not 
int is_builtin(char	*cmd)
{
	if (ft_strncmp(cmd, "echo", 4))
		return (1);
	else if (ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3))
		return (1);
	else if (ft_strncmp(cmd, "export", 6))
		return (1);
	else if (ft_strncmp(cmd, "unset", 5))
		return (1);
	else if (ft_strncmp(cmd, "env", 6))
		return (1);
	else if (ft_strncmp(cmd, "exit", 6))
		return (1);
	else
		return (0);
}