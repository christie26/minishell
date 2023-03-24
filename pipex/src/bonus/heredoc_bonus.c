/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:52:29 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 14:14:32 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

char	*random_name(void)
{
	char	*tmp_file;
	int		i;
	int		j;

	tmp_file = (char *)malloc(sizeof(char) * 2);
	ft_err_msg(!tmp_file, "Fail to malloc();", __FILE__, __LINE__);
	i = '1';
	while (i++ < '~')
	{
		j = '1';
		while (j++ < '~')
		{
			tmp_file[0] = i;
			tmp_file[1] = j;
			if (access(tmp_file, F_OK))
				return (tmp_file);
		}
	}
	free(tmp_file);
	return (0);
}

void	here_doc(t_data *data)
{
	char	*buf;
	char	*tmp_file;
	int		fd;
	size_t	len;

	tmp_file = random_name();
	ft_err_msg(!tmp_file, "Fail to find random file name", __FILE__, __LINE__);
	fd = open(tmp_file, O_CREAT | O_WRONLY, 0644);
	ft_err_sys(fd == -1, __FILE__, __LINE__);
	len = ft_strlen(data->limiter);
	buf = get_next_line(STDIN_FILENO);
	while (ft_strncmp(buf, data->limiter, len) || buf[len] != '\n')
	{
		write(fd, buf, ft_strlen(buf));
		free(buf);
		buf = get_next_line(STDIN_FILENO);
	}
	free(buf);
	close_fd(fd, __FILE__, __LINE__);
	data->infile = tmp_file;
}
