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

int	ft_export(char *cmd, char **options, char **env)
{
	char	**new_env;
	int		i;
	int		number;

	options++;
	if (check_input(*options))
		return (1);
	i = 0;
	while (env[i])
		i++;
	number = i;
	new_env = malloc(sizeof(char *) * number);
	ft_err_msg_exit(!new_env, "Fail malloc", __FILE__, __LINE__);
	i = 0;
	while (i < number)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(*options);
	ft_err_msg_exit(!new_env[i], "Fail to malloc", __FILE__, __LINE__);
	update_myvar(new_env);
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

int	ft_env(char *cmd, char **options, char **env)
{
	options++;
	if (*options)
	{
		ft_err_msg(1, "We don't need arguments", __FILE__, __LINE__);
		return (1);
	}
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
	(void)(cmd);
	return (0);
}
