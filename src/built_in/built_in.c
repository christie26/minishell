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
	if (!ft_strcmp(*options, "-n"))
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
	options++;
	ft_err_sys(!*options, __FILE__, __LINE__);
	ft_err_sys(chdir(*options) == -1, __FILE__, __LINE__);
    (void)(cmd);
    (void)(env);
	return (0);
}

int ft_pwd(char *cmd, char **options, char **env)
{
	char	buf[1024];

	ft_err_sys((getcwd(buf, 1024) == NULL), __FILE__, __LINE__);
	ft_putendl_fd(buf, 1);
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
	options++;
	if (*options)
	{
		ft_err_msg(1, "We don't need arguments", __FILE__, __LINE__);
		return (1);
	}
	// ft_err_msg((int)(*options), "We don't need arguments", __FILE__, __LINE__);
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
    (void)(cmd);
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
int ft_builtin(char	**argv, char **env)
{
	char	*cmd;

	cmd = argv[0];

	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(cmd, argv, env));
	else if (!ft_strcmp(cmd, "cd")) 
		return (ft_cd(cmd, argv, env));
	else if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd(cmd, argv, env));
	else if (!ft_strcmp(cmd, "export"))
		return (ft_export(cmd, argv, env));
	else if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(cmd, argv, env));
	else if (!ft_strcmp(cmd, "env"))
		return (ft_env(cmd, argv, env));
	else if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(cmd, argv, env));
	else
		return (0);
}

// check cmd if it's builtin cmd or not 
int is_builtin(char	*cmd)
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