/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:52 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:49:53 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_builtin.h"

char	**get_env(char **env)
{
	int		i;
	int		j;
	int		number;
	char	**tmp_env;

	number = 0;
	while (env[number])
		number++;
	tmp_env = malloc(sizeof(char *) * (number + 1));
	if (!tmp_env)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (j < number)
	{
		if (!ft_strncmp(env[j], "?=", 2))
		{
			j++;
			continue ;
		}
		tmp_env[i++] = env[j++];
	}
	tmp_env[i] = 0;
	tmp_env[j] = 0;
	return (tmp_env);
}

char	**init_envp(char **envp)
{
	int		i;
	int		var_number;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	var_number = i;
	new_env = malloc(sizeof(char *) * (var_number + 1));
	i = 0;
	while (i < var_number)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = 0;
	g_exit_status = 0;
	return (new_env);
}

char	*get_value(char *key, char **env)
{
	char	*env_line;
	char	*test_key;
	char	*value;
	int		i;

	while (*env)
	{
		env_line = *env;
		i = ft_strchr(env_line, '=') - env_line;
		test_key = ft_substr(env_line, 0, i);
		if (ft_strcmp(test_key, key) == 0)
		{
			free(test_key);
			value = ft_substr(env_line, i + 1, ft_strlen(env_line));
			if (!value)
				exit(EXIT_FAILURE);
			return (value);
		}
		free(test_key);
		env++;
	}
	value = ft_strdup("");
	if (!value)
		exit(EXIT_FAILURE);
	return (value);
}

int	ft_env(char *cmd, char **options, char **env)
{
	int		i;

	options++;
	if (*options)
	{
		error_command_msg("env", "We don't need arguments\n");
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "?=", 2) && ft_strchr(env[i], '=') != NULL)
			ft_putendl_fd(env[i], 1);
		i++;
	}
	(void)(cmd);
	return (0);
}
