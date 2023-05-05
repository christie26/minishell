#ifndef MINI_EXEC_H

# define MINI_EXEC_H

# define READ 0
# define WRITE 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>

# include "libft.h"
# include "get_next_line.h"
# include "../model.h"
# include "../error.h"

int		heredoc_center(t_data *data, t_pipeline *pipeline);
void	heredoc_unlink(t_pipeline *pipeline);
char	*heredoc_open(t_redirect *redirect, char **env);

// get path
char	**get_path(char **env);
char	*check_access(char *cmd, char **path);

// child & parent process
void	child_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i);
void	parent_process(t_data *data, int *p_fd, int i, pid_t cpid);
int		redirection_center(t_redirect *redirect);
char	**get_env(char **env);

// utils
void	ft_close(int fd);
void	ft_dup2(int fd_from, int fd_to);
void	get_short_exit(int exit_status);
void	set_exit_status(t_data *data, int g_exit_status);
void	free_path(char **path);

// built-in
int		ft_builtin(char **argv, t_data *data);
int		is_builtin(char *cmd);
void	add_variable(char *key_value, t_data *data);

// expand part
char	*get_expanded_string(char *str, char **my_env);

#endif
