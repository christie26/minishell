#include "built_in.h"

char	**get_env(char **env)
{
	int		i;
	int		number;
	char	**tmp_env;

	i = 0;
	while (env[i])
		i++;
	number = i;
	tmp_env = malloc(sizeof(char *) * (number + 1));
	ft_err_msg_exit(!tmp_env, MALLOC_ERROR, __FILE__, __LINE__);
	i = 0;
	while (i < number)
	{
		if (ft_strncmp(env[i], "?=", 2))
				tmp_env[i] = env[i];
		i++;
	}
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
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

// put my_env as parameter here
char	*get_value(char *key, char **env)
{
	char	*env_line;
	char	*test_key;
	int		i;

	while (*env)
	{
		env_line = *env;
		i = -1;
		while (env_line[++i])
			if (env_line[i] == '=')
				break ;
		test_key = ft_substr(env_line, 0, i);
		if (ft_strcmp(test_key, key) == 0)
		{
			free(test_key);
			return (ft_substr(env_line, i + 1, ft_strlen(env_line)));
		}
		free(test_key);
		env++;
	}
	return (0);
}

int	ft_env(char *cmd, char **options, char **env)
{
	int	i;

	options++;
	if (*options)
	{
		ft_err_msg(1, "We don't need arguments", __FILE__, __LINE__);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	(void)(cmd);
	return (0);
}
