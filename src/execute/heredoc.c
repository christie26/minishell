
#include "./mini_exec.h"

void	heredoc_unlink(t_pipeline *pipeline)
{
	t_redirect *redirect;

    while (pipeline)
    {
        redirect = pipeline->cmd_block->redirect;
        while(redirect)
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

void	heredoc_open(t_redirect *redirect)
{
	char	*buf;
	char	*tmp_file;
	int		fd;
	size_t	len;

	tmp_file = random_name();
	ft_err_msg(!tmp_file, "Fail to find random file name", __FILE__, __LINE__);
	fd = open(tmp_file, O_CREAT | O_WRONLY, 0644);
	ft_err_sys(fd == -1, __FILE__, __LINE__);
	len = ft_strlen(redirect->filename);
	buf = get_next_line(STDIN_FILENO);
	while (ft_strncmp(buf, redirect->filename, len) || buf[len] != '\n')
	{
		// add expand part here !!
		write(fd, buf, ft_strlen(buf));
		free(buf);
		buf = get_next_line(STDIN_FILENO);
	}
	free(buf);
	close_fd(fd, __FILE__, __LINE__);
	redirect->filename = tmp_file;
}

//여러개 들어오면 하나씩 처리 
void    heredoc_center(t_pipeline *pipeline)
{
    t_redirect *redirect;

    while (pipeline)
    {
        redirect = pipeline->cmd_block->redirect;
        while(redirect)
        {
            if (redirect->type == 2)
                heredoc_open(redirect);
            redirect = redirect->next;
        }
        pipeline = pipeline->next;
    }
}