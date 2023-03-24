/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:13:38 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 13:44:29 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/src/libft.h"
# include "../libft/src/get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1

typedef struct s_data {
	int		number;
	int		offset;
	char	*limiter;
	char	**cmd;
	char	***cmd_options;
	int		read_fd;
	char	*infile;
	char	*outfile;
	pid_t	*pid_set;
}	t_data;

// handle error 
void	ft_err_msg(int condition, char *error_message, char *file, int line);
void	ft_err_sys(int condition, char *file, int line);

//utils
void	close_fd(int fd, char *file, int line);
void	duplicate_fd(int read_end, int write_end, char *file, int line);
void	free_array(char **item, int i);

// here_doc
void	here_doc(t_data *data);

// set path and check accessibility
int		pipex_set(char **av, char **env, t_data *data);

// fork and execute 
int		pipex_execute(t_data *data, char **env);

#endif
