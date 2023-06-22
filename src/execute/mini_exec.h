/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:51:12 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 19:58:30 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	mini_execute(t_pipeline *pipeline, t_data *data);

// heredoc
int		heredoc_center(t_data *data, t_pipeline *pipeline);
void	heredoc_unlink(t_pipeline *pipeline);
char	*get_tmp_file(void);
void	heredoc_write(int fd, char *filename, char **env);

// get path
char	**set_path(char **env);
char	*check_access(char *cmd, char **path);
int		is_exist(char *cmd);
char	*get_cmd_path(char *cmd, char **path);

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
int		is_directory(char *cmd);
int		have_permission(char *cmd);
int		is_exist(char *cmd);

// error handling
int		error_command_msg(char *cmd, char *message);
int		error_command(char *cmd);

#endif
