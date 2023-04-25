#include "built_in.h"

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
	ft_err_msg_exit(!tmp_env, MALLOC_ERROR, __FILE__, __LINE__);
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
			ft_err_msg_exit(!value, MALLOC_ERROR, __FILE__, __LINE__);
			return (value);
		}
		free(test_key);
		env++;
	}
	value = ft_strdup("");
	ft_err_msg_exit(!value, MALLOC_ERROR, __FILE__, __LINE__);
	return (value);
}

int	ft_env(char *cmd, char **options, char **env)
{
	int		i;
	char	**print_env;

	print_env = get_env(env);
	options++;
	if (*options)
	{
		ft_err_msg(1, "We don't need arguments", __FILE__, __LINE__);
		return (127);
	}
	i = 0;
	while (print_env[i])
	{
		ft_putendl_fd(print_env[i], 1);
		i++;
	}
	free(print_env);
	(void)(cmd);
	return (0);
}
