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
	if (!path)
		exit(EXIT_FAILURE);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
			exit(EXIT_FAILURE);
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
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		if (!path_cmd)
			exit(EXIT_FAILURE);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (0);
}
