#include "./built_in.h"

void	set_old_pwd(char *option, t_data *data)
{
	char	*key_value;
	char	old_pwd[1024];
	char	*old_pwd_from_env;

	old_pwd_from_env = get_value("OLDPWD", data->my_env);
	if (old_pwd_from_env[0] == 0 && !ft_strcmp(option, "-"))
		return ;
	free(old_pwd_from_env);
	ft_err_sys((getcwd(old_pwd, 1024) == NULL), __FILE__, __LINE__);
	key_value = ft_strjoin("OLDPWD=", old_pwd);
	add_variable(key_value, data);
	free(key_value);
}

void	set_pwd(t_data *data)
{
	char	*key_value;
	char	pwd[1024];

	ft_err_sys((getcwd(pwd, 1024) == NULL), __FILE__, __LINE__);
	key_value = ft_strjoin("PWD=", pwd);
	add_variable(key_value, data);
	free(key_value);
}

int	move_to_home(char **env)
{
	char	*home;
	int		return_value;

	home = get_value("HOME", env);
	if (!ft_strcmp(home, ""))
		return (ft_err_msg(1, HOME_ERROR, __FILE__, __LINE__));
	return_value = ft_err_sys(chdir(home) == -1, __FILE__, __LINE__);
	free(home);
	return (return_value);
}

int	move_to_old_pwd(char **env)
{
	char	*old_pwd;
	int		return_value;

	old_pwd = get_value("OLDPWD", env);
	if (!ft_strcmp(old_pwd, ""))
		return (ft_err_msg(1, OLDPWD_ERROR, __FILE__, __LINE__));
	return_value = ft_err_sys(chdir(old_pwd) == -1, __FILE__, __LINE__);
	free(old_pwd);
	return (return_value);
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
		return_value = ft_err_sys(chdir(*options) == -1, __FILE__, __LINE__);
	if (return_value == 0)
		set_pwd(data);
	return (return_value);
}
