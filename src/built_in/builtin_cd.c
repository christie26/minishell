#include "./mini_builtin.h"

void	set_old_pwd(char *option, t_data *data)
{
	char	*key_value;
	char	old_pwd[1024];
	char	*old_pwd_from_env;

	old_pwd_from_env = get_value("OLDPWD", data->my_env);
	if (old_pwd_from_env[0] == 0 && !ft_strcmp(option, "-"))
		return ;
	free(old_pwd_from_env);
	if (getcwd(old_pwd, 1024) == NULL)
		error_command("cd");
	key_value = ft_strjoin("OLDPWD=", old_pwd);
	add_variable(key_value, data);
	free(key_value);
}

void	set_pwd(t_data *data)
{
	char	*key_value;
	char	pwd[1024];

	if (getcwd(pwd, 1024) == NULL)
		error_command("cd");
	key_value = ft_strjoin("PWD=", pwd);
	add_variable(key_value, data);
	free(key_value);
}

int	move_to_home(char **env)
{
	char	*home;

	home = get_value("HOME", env);
	if (!ft_strcmp(home, ""))
	{
		error_command_msg("cd", HOME_ERROR);
		free(home);
		return (EXIT_FAILURE);
	}
	if (chdir(home) == -1)
	{
		error_command("cd");
		free(home);
		return (EXIT_FAILURE);
	}
	else
	{
		free(home);
		return (EXIT_SUCCESS);
	}
}

int	move_to_old_pwd(char **env)
{
	char	*old_pwd;

	old_pwd = get_value("OLDPWD", env);
	if (!ft_strcmp(old_pwd, ""))
	{
		error_command_msg("cd", OLDPWD_ERROR);
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	if (chdir(old_pwd) == -1)
	{
		error_command("cd");
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	else
	{
		free(old_pwd);
		return (EXIT_SUCCESS);
	}
}

int	ft_cd(t_data *data, char **options, char **env)
{
	int		return_value;

	options++;
	set_old_pwd(*options, data);
	if (!*options || !ft_strcmp(*options, "~"))
		return_value = move_to_home(env);
	else if (*options && !ft_strcmp(*options, "-"))
		return_value = move_to_old_pwd(env);
	else
	{
		if (chdir(*options) == -1)
		{
			error_command("cd");
			return_value = 1;
		}
		else
			return_value = 0;
	}
	if (return_value == 0)
		set_pwd(data);
	return (return_value);
}
