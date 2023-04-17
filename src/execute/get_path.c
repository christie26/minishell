#include "./mini_exec.h"

char	**get_path(char **env)
{
	int		i;
	char	*tmp;
	char	**path;

	while (*env++)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			break ;
	}
	path = ft_split((*env + 5), ':');
	ft_err_msg_exit(!path, MALLOC_ERROR, __FILE__, __LINE__);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		ft_err_msg_exit(!path[i], MALLOC_ERROR, __FILE__, __LINE__);
		free(tmp);
		i++;
	}
	return (path);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		ft_err_msg_exit(!path_cmd, MALLOC_ERROR, __FILE__, __LINE__);
		if (access(path_cmd, X_OK) == 0)
		{
			free(cmd);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	return (0);
}
