/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:51:21 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:51:41 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

int	redirection_1(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		error_command(file);
		return (1);
	}
	ft_dup2(fd, 0);
	ft_close(fd);
	return (0);
}

int	redirection_2(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		error_command(file);
		return (1);
	}
	ft_dup2(fd, 0);
	ft_close(fd);
	return (0);
}

int	redirection_3(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_command(file);
		return (1);
	}	
	ft_dup2(fd, 1);
	ft_close(fd);
	return (0);
}

int	redirection_4(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		error_command(file);
		return (1);
	}	
	ft_dup2(fd, 1);
	ft_close(fd);
	return (0);
}

int	redirection_center(t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == 1)
		{
			if (redirection_1(redirect->filename))
				return (1);
		}
		else if (redirect->type == 2)
		{
			if (redirection_2(redirect->filename))
				return (1);
		}
		else if (redirect->type == 3)
		{
			if (redirection_3(redirect->filename))
				return (1);
		}
		else
		{
			if (redirection_4(redirect->filename))
				return (1);
		}
		redirect = redirect->next;
	}
	return (0);
}
