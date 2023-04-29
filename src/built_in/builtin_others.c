#include "./mini_builtin.h"

int	ft_pwd(char *cmd, char **options, char **env)
{
	char	buf[1024];

	ft_err_sys((getcwd(buf, 1024) == NULL), __FILE__, __LINE__);
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
	ft_err_msg_exit(!result, MALLOC_ERROR, __FILE__, __LINE__);
	free(s1);
	tmp = result;
	result = ft_strjoin(tmp, s2);
	ft_err_msg_exit(!result, MALLOC_ERROR, __FILE__, __LINE__);
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
		return (0);
	result = ft_strdup(*options++);
	ft_err_msg_exit(!result, MALLOC_ERROR, __FILE__, __LINE__);
	while (*options)
		result = join_with_space(result, *options++);
	if (endl)
		printf("%s\n", result);
	else
		printf("%s", result);
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
	{
		ft_err_msg(1, "too many arguments", __FILE__, __LINE__);
		return (1);
	}
	else if (i == 1)
		exit(short_exit_status);
	options++;
	if (!ft_strisnum(*options))
	{
		ft_err_msg(1, "numeric argument required", __FILE__, __LINE__);
		exit(255);
	}
	exit(ft_atoi(*options));
	(void)(cmd);
	(void)(env);
	return (0);
}
