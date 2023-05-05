/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:50:01 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:50:01 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_builtin.h"

int	ft_pwd(char *cmd, char **options, char **env)
{
	char	buf[1024];

	if (getcwd(buf, 1024) == NULL)
		error_command("pwd");
	ft_putendl_fd(buf, 1);
	(void)(cmd);
	(void)(options);
	(void)(env);
	return (0);
}

char	*join_with_space(char *s1, char *s2)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin(s1, " ");
	if (!result)
		exit(EXIT_FAILURE);
	free(s1);
	tmp = result;
	result = ft_strjoin(tmp, s2);
	if (!result)
		exit(EXIT_FAILURE);
	free(tmp);
	return (result);
}

int	ft_echo(char **options, char **env)
{
	char	*result;
	int		endl;

	options++;
	endl = 1;
	if (*options && !ft_strcmp(*options, "-n"))
	{
		options++;
		endl = 0;
	}
	if (!*options)
		result = ft_strdup("");
	else
	{
		result = ft_strdup(*options++);
		if (!result)
			exit(EXIT_FAILURE);
		while (*options)
			result = join_with_space(result, *options++);
	}
	if (endl)
		printf("%s\n", result);
	else
		printf("%s", result);
	free(result);
	(void)(env);
	return (0);
}

int	ft_exit(char *cmd, char **options, char **env)
{
	int	i;

	i = 0;
	while (options[i])
		i++;
	if (i > 2)
		return (error_command_msg("exit", "too many arguments\n"));
	else if (i == 1)
		exit(g_exit_status);
	options++;
	if (!ft_strisnum(*options))
	{
		error_command_msg("exit", EXIT_ERROR);
		exit(255);
	}
	exit(ft_atoi(*options));
	(void)(cmd);
	(void)(env);
	return (0);
}
