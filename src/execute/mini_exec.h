#ifndef MINI_EXEC_H

# define MINI_EXEC_H

# define READ 0
# define WRITE 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "libft.h"
# include "get_next_line.h"
# include "../model.h"
# include "../error.h"
# include "../built_in/mini_builtin.h"
# include "../parse/mini_parse.h"

int		mini_execute(t_pipeline *pipeline, t_data *data);

// heredoc
int		heredoc_center(t_data *data, t_pipeline *pipeline);
void	heredoc_unlink(t_pipeline *pipeline);
char	*heredoc_open(t_redirect *redirect, char **env);

// get path
char	**get_path(char **env);
char	*check_access(char *cmd, char **path);
int		is_exist(char *cmd);

// child & parent process
void	child_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i);
void	parent_process(t_data *data, int *p_fd, int i, pid_t cpid);

// redirection
int		redirection_center(t_redirect *redirect);

// utils
void	ft_close(int fd);
void	ft_dup2(int fd_from, int fd_to);
void	get_short_exit(int exit_status);
void	free_path(char **path);

#endif
