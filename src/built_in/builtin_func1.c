#include "./built_in.h"

int	ft_cd(char *cmd, char **options, char **env)
{
	char	*home;

	options++;
	if (!*options || !ft_strcmp(*options, "~"))
	{
		home = get_value("HOME", env);
		if (!home)
			return (ft_err_msg(1, HOME_ERROR, __FILE__, __LINE__));
		ft_err_sys(chdir(home) == -1, __FILE__, __LINE__);
		free(home);
		return (0);
	}
	ft_err_sys(chdir(*options) == -1, __FILE__, __LINE__);
	(void)(cmd);
	return (0);
}

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

int	ft_echo(char *cmd, char **options, char **env)
{
	int	endl;

	options++;
	endl = 1;
	if (!*options)
		return (0);
	if (!ft_strcmp(*options, "-n"))
	{
		options++;
		endl = 0;
	}
	while (*options)
	{
		ft_putstr_fd(*options, 1);
		options++;
		if (*options)
			ft_putchar_fd(' ', 1);
	}
	if (endl)
		ft_putchar_fd('\n', 1);
	(void)(cmd);
	printf("$? = %s\n", get_value("?", env));
	return (0);
}

int	ft_exit(char *cmd, char **options, char **env)
{
	exit(0);
	(void)(cmd);
	(void)(options);
	(void)(env);
	return (0);
}
