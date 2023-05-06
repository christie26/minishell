/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:51:18 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:51:19 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

int	error_command_msg(char *cmd, char *message)
{
	char	*cmd_extra;
	char	*shell;
	char	*with_message;

	cmd_extra = ft_strjoin(cmd, ": ");
	if (!cmd_extra)
		exit(EXIT_FAILURE);
	shell = ft_strjoin("yo shell: ", cmd_extra);
	if (!shell)
		exit(EXIT_FAILURE);
	free(cmd_extra);
	with_message = ft_strjoin(shell, message);
	free(shell);
	if (!with_message)
		exit(EXIT_FAILURE);
	write(2, with_message, ft_strlen(with_message));
	free(with_message);
	return (EXIT_FAILURE);
}

int	error_command(char *cmd)
{
	char	*shell;

	shell = ft_strjoin("yo shell: ", cmd);
	if (!shell)
		exit(EXIT_FAILURE);
	perror(shell);
	free(shell);
	return (EXIT_FAILURE);
}
