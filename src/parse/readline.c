/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:32:37 by yoonsele          #+#    #+#             */
/*   Updated: 2023/06/22 18:19:32 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parse.h"

t_pipeline	*my_parse(char *str, char **my_env)
{
	t_pipeline	*pipe_list;
	t_token		*tokens;

	(void)my_env;
	pipe_list = NULL;
	tokens = NULL;
	create_tokens(&tokens, str);
	if (!tokens)
		return (NULL);
	add_history(str);
	expand_tokens(&tokens, my_env);
	if (!tokens)
		return (NULL);
	splitting_tokens(&tokens);
	quote_remove_tokens(&tokens);
	if (!tokens)
		return (NULL);
	create_pipeline_list(&pipe_list, tokens);
	ft_token_lstclear(&tokens);
	return (pipe_list);
}

void	readline_exit(void)
{
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[10C", STDOUT_FILENO);
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}
