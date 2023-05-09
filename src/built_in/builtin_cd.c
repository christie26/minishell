/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:45 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:49:48 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_builtin.h"

void	set_pwd(char *current_pwd, t_data *data)
{
	char	*pwd_value;
	char	pwd[1024];
	char	*oldpwd_value;

	if (getcwd(pwd, 1024) == NULL)
		error_command("cd");
	pwd_value = ft_strjoin("PWD=", pwd);
	oldpwd_value = ft_strjoin("OLDPWD=", current_pwd);
	add_variable(pwd_value, data);
	add_variable(oldpwd_value, data);
	free(pwd_value);
	free(oldpwd_value);
}

int	move_to_home(char **env)
{
	char	*home;

	home = get_value("HOME", env);
	if (home && !ft_strcmp(home, ""))
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
	if (old_pwd && !ft_strcmp(old_pwd, ""))
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
	char	current_pwd[1024];

	options++;
	return_value = 0;
	if (getcwd(current_pwd, 1024) == NULL)
		error_command("cd");
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
	}
	if (return_value == 0)
		set_pwd(current_pwd, data);
	return (return_value);
}
