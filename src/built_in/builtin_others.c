#include "./built_in.h"

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

int	ft_echo(char **options, char **env)
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
	// We have to move this to 'expand' part
	if (!ft_strncmp(*options, "$?", 2))
	{
		ft_putstr_fd(get_value("?", env), 1);
		*options += 2;
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
