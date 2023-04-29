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
				unlink(redirect->filename);
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
	ft_err_msg_exit(!tmp_file, MALLOC_ERROR, __FILE__, __LINE__);
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

void	heredoc_open(t_redirect *redirect, char **env)
{
	char	*buf;
	char	*expanded;
	char	*tmp_file;
	int		fd;
	size_t	len;

	tmp_file = random_name();
	ft_err_msg_exit(!tmp_file, TMP_FILE_ERROR, __FILE__, __LINE__);
	fd = open(tmp_file, O_CREAT | O_WRONLY, 0644);
	ft_err_sys(fd == -1, __FILE__, __LINE__);
	len = ft_strlen(redirect->filename);
	buf = get_next_line(STDIN_FILENO);
	while (ft_strncmp(buf, redirect->filename, len) || buf[len] != '\n')
	{
		expanded = get_expanded_string(buf, env);
		if (write(fd, expanded, ft_strlen(expanded)) == -1)
			ft_err_sys(1, __FILE__, __LINE__);
		free(buf);
		buf = get_next_line(STDIN_FILENO);
	}
	free(buf);
	ft_close(fd, __FILE__, __LINE__);
	free(redirect->filename);
	redirect->filename = tmp_file;
}

void	heredoc_center(t_pipeline *pipeline, char **env)
{
	t_redirect	*redirect;

	while (pipeline)
	{
		redirect = pipeline->cmd_block->redirect;
		while (redirect)
		{
			if (redirect->type == 2)
				heredoc_open(redirect, env);
			redirect = redirect->next;
		}
		pipeline = pipeline->next;
	}
}
