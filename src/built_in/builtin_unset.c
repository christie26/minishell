#include "mini_builtin.h"

void	remove_variable(int index_env, t_data *data, int number)
{
	char	**env;
	char	**new_env;
	int		i;
	int		j;

	env = data->my_env;
	new_env = malloc(sizeof(char *) * number);
	if (!new_env)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (j < number)
	{
		if (j == index_env)
		{
			j++;
			continue ;
		}
		new_env[i++] = env[j++];
	}
	free(env[index_env]);
	new_env[i] = 0;
	data->my_env = new_env;
	free(env);
}

int	check_input_unset(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '=' || !(ft_isalpha(input[0]) || input[0] == '_'))
		return (error_command_msg("unset", EXPORT_ERROR));
	while (input[i])
	{
		if (!(ft_isalpha(input[i]) || input[i] == '_'))
			return (error_command_msg("unset", EXPORT_ERROR));
		i++;
	}
	return (0);
}

int	ft_unset(char **options, t_data *data)
{
	int		index_env;
	int		number;

	number = 0;
	while (data->my_env[number])
		number++;
	options++;
	if (!*options)
		return (0);
	if (check_input_unset(*options))
		return (1);
	index_env = key_exist(*options, data, ft_strlen(*options));
	if (index_env != -1)
		remove_variable(index_env, data, number);
	return (0);
}
