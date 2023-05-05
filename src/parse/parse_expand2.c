/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:52:09 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:52:09 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parse.h"

void	expand_tokens(t_token **token_list, char **my_env)
{
	t_token	*cur_token;
	int		is_here_doc;
	char	*content;

	cur_token = *token_list;
	is_here_doc = 0;
	while (cur_token)
	{
		if (cur_token->type == OPERATOR || is_here_doc)
		{
			is_here_doc = (ft_strcmp(cur_token->value, "<<") == 0);
			cur_token = cur_token->next;
			continue ;
		}
		content = get_expanded_string(cur_token->value, my_env);
		if (content == NULL)
		{
			ft_token_lstclear(token_list);
			return ;
		}
		free(cur_token->value);
		cur_token->value = content;
		cur_token = cur_token->next;
	}
}

char	*word_list_join(t_list *word_list)
{
	char	*result;
	char	*temp;
	t_list	*word_list_iter;

	result = ft_strdup("");
	if (result == NULL)
		exit(EXIT_FAILURE);
	word_list_iter = word_list;
	while (word_list_iter)
	{
		temp = result;
		result = ft_strjoin(result, word_list_iter->content);
		if (result == NULL)
			exit(EXIT_FAILURE);
		free(temp);
		word_list_iter = word_list_iter->next;
	}
	ft_lstclear(&word_list, free);
	return (result);
}
