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