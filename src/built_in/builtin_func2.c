#include "built_in.h"

int	check_input(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!input)
		return (ft_err_msg(1, "No input", __FILE__, __LINE__));
	while (input[i])
	{
		if (input[i] == '=')
			count++;
		i++;
	}
	if (count != 1)
		return (ft_err_msg(1, "Invalud input", __FILE__, __LINE__));
	return (0);
}

void	update_myvar(char **new_env)
{
	free(my_env);
	my_env = new_env;
}

int	if_key_exist(char *key_value, char **env)
{
	int	i;
	int	index_env;

	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
			break ;
		i++;
	}
	index_env = 0;
	while (env[index_env])
	{
		if (!ft_strncmp(key_value, env[index_env], i + 1))
		{
			free(env[index_env]);
			env[index_env] = key_value;
			return (1);
		}
		index_env++;
	}
	return (0);
}

void	add_var_update(char *key_value, char **env)
{
	char	**new_env;
	int		i;
	int		number;

	if (if_key_exist(key_value, env))
		return ;
	i = 0;
	while (env[i])
		i++;
	number = i;
	new_env = malloc(sizeof(char *) * (number + 1));
	ft_err_msg_exit(!new_env, MALLOC_ERROR, __FILE__, __LINE__);
	i = 0;
	while (i < number)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(key_value);
	ft_err_msg_exit(!new_env[i], MALLOC_ERROR, __FILE__, __LINE__);
	new_env[i + 1] = 0;
	update_myvar(new_env);
}

int	ft_export(char *cmd, char **options, char **env)
{
	options++;
	if (check_input(*options))
		return (1);
	add_var_update(*options, env);
	(void)(cmd);
	return (0);
}

int	ft_unset(char *cmd, char **options, char **env)
{
	printf("execute unset\n");
	(void)(cmd);
	(void)(options);
	(void)(env);
	return (0);
}
