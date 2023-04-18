#ifndef MINI_EXEC_H

# define MINI_EXEC_H

# define READ 0
# define WRITE 1

int exit_status;

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"
# include "../model.h"
# include "../error.h"

int		mini_execute(t_pipeline *pipeline, char **env);
void	heredoc_center(t_pipeline *pipeline);
void	heredoc_unlink(t_pipeline *pipeline);

// get path
char	**get_path(char **env);
char	*check_access(char *cmd, char **path);

// child & parent process
void	child_process(t_data *data, t_pipeline *pipeline, int *p_fd, int i);
void	parent_process(t_data *data, int *p_fd, int i, pid_t cpid);
void	redirection_center(t_redirect *redirect);
char	**get_env(char **env);


// utils
void	ft_close(int fd, char *file, int line);

// built-in
int		ft_builtin(char **argv, char **env);
int		is_builtin(char *cmd);
// int		ft_export(char *cmd, char **options, char **env);
void	add_var_update(char *key_value, char **env);


#endif
