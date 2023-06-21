/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:56 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 20:30:45 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_builtin.h"

int	check_input(char *input)
{
	int	i;
	int	count;
	int	key;

	i = 0;
	count = 0;
	key = 1;
	if (input[0] == '=' || !(ft_isalpha(input[0]) || input[0] == '_'))
		return (error_command_msg("export", EXPORT_ERROR));
	while (input[i])
	{
		if (input[i] == '=')
		{
			key = 0;
			count++;
		}
		if (key && (!(ft_isalpha(input[i]) || input[i] == '_')))
			return (error_command_msg("export", EXPORT_ERROR));
		i++;
	}
	if (count != 1)
		return (error_command_msg("export", "Invalid input\n"));
	return (0);
}

int	key_exist(char *key, t_data *data, int len)
{
	int		index_env;
	char	**env;

	env = data->my_env;
	index_env = 0;
	while (env[index_env])
	{
		if (!ft_strncmp(key, env[index_env], len) && env[index_env][len] == '=')
			return (index_env);
		index_env++;
	}
	return (-1);
}

int	if_key_exist(char *key_value, t_data *data)
{
	char	**env;
	int		index_env;
	char	*tmp ;
	int		i;

	env = data->my_env;
	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
			break ;
		i++;
	}
	index_env = key_exist(key_value, data, i);
	if (index_env != -1)
	{
		tmp = env[index_env];
		env[index_env] = ft_strdup(key_value);
		free(tmp);
		return (1);
	}
	return (0);
}

void	add_variable(char *key_value, t_data *data)
{
	char	**env;
	char	**new_env;
	int		i;
	int		number;

	env = data->my_env;
	if (if_key_exist(key_value, data))
		return ;
	i = 0;
	while (env[i])
		i++;
	number = i;
	new_env = malloc(sizeof(char *) * (number + 2));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < number)
		new_env[i] = env[i];
	new_env[i] = ft_strdup(key_value);
	if (!new_env[i])
		exit(EXIT_FAILURE);
	new_env[i + 1] = 0;
	data->my_env = new_env;
	free(env);
}

int	ft_export(char **options, t_data *data)
{
	int		return_value;
	int		i;
	char	**env;

	return_value = 0;
	options++;
	if (!(*options))
	{
		env = get_env(data->my_env);
		i = -1;
		while (env[++i])
			print_variable(env[i]);
		free(env);
	}
	while (*options)
	{
		if (check_input(*options))
		{
			options++;
			return_value = 1;
			continue ;
		}
		add_variable(*options, data);
		options++;
	}
	return (return_value);
}
