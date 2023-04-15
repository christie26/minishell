
#ifndef MINI_EXEC_H

# define MINI_EXEC_H

# define READ 0
# define WRITE 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "../../libft/includes/libft.h"
# include "../model.h"

int     mini_execute(t_pipeline *pipeline, char **env);

// get path
char	**get_path(char **env);
char	*check_access(char *cmd, char **path);

// child & parent process
void	child_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i);
void	parent_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i, pid_t cpid);

// utils
void	close_fd(int fd, char *file, int line);

// built-in
int     ft_builtin(t_pipeline *pipeline, char **env);
int     is_builtin(char *cmd);

// ft_error
void	ft_err_msg(int condition, char *error_message, char *file, int line);
void	ft_err_sys(int condition, char *file, int line);

#endif
