/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:13:33 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 13:43:34 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1

typedef struct s_data {
	char	*cmd[2];
	char	**cmd_options[2];
	pid_t	pid_set[2];
	int		read_fd;
	char	*infile;
	char	*outfile;
}	t_data;

// handle error
void	ft_err_msg(int condition, char *error_message, char *file, int line);
void	ft_err_sys(int condition, char *file, int line);

//utils
void	close_fd(int fd, char *file, int line);
void	duplicate_fd(int read_end, int write_end, char *file, int line);
void	free_array(char **item, int i);

// set path and check accessibility
int		pipex_set(char **av, char **env, t_data *data);

// fork and execute 
int		pipex_execute(t_data *data, char **env);

#endif
