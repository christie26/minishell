/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:50:44 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:50:45 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

void	heredoc_unlink(t_pipeline *pipeline)
{
	t_redirect	*redirect;

	while (pipeline)
	{
		redirect = pipeline->cmd_block->redirect;
		while (redirect)
		{
			if (redirect->type == 2)
			{
				unlink(redirect->filename);
			}
			redirect = redirect->next;
		}
		pipeline = pipeline->next;
	}
}

char	*random_name(void)
{
	char	*tmp_file;
	int		i;
	int		j;

	tmp_file = (char *)malloc(sizeof(char) * 16);
	if (!tmp_file)
		exit(EXIT_FAILURE);
	tmp_file[0] = 0;
	ft_strlcat(tmp_file, "/tmp/tmp_file", 14);
	i = '/';
	while (i++ < '9')
	{
		j = '/';
		while (j++ < '9')
		{
			tmp_file[13] = i;
			tmp_file[14] = j;
			tmp_file[15] = 0;
			if (access(tmp_file, F_OK))
				return (tmp_file);
		}
	}
	free(tmp_file);
	return (0);
}

void	heredoc_write(int fd, char *delimeter, char **env)
{
	char	*buf;
	char	*expanded;

	buf = readline("> ");
	while (buf && ft_strcmp(buf, delimeter))
	{
		expanded = get_expanded_string(buf, env);
		if (write(fd, expanded, ft_strlen(expanded)) == -1)
			error_command("heredoc");
		free(expanded);
		free(buf);
		buf = readline("> ");
	}
	if (buf)
		free(buf);
	ft_close(fd);
}

char	*get_tmp_file(void)
{
	char	*tmp_file;

	tmp_file = random_name();
	if (!tmp_file)
	{
		error_command_msg("heredoc", TMP_FILE_ERROR);
		exit(EXIT_FAILURE);
	}
	return (tmp_file);
}
