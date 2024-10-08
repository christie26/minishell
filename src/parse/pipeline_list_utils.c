/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:32:56 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 20:32:56 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parse.h"

t_pipeline	*ft_pipeline_lstnew(t_token **token_list)
{
	t_pipeline	*new_pipeline;
	t_cmd_block	*new_cmd_block;

	if ((*token_list)->type == OPERATOR && \
		ft_strcmp("|", (*token_list)->value) == 0)
	{
		error_command_msg("parse", UNEXPECTED_TOKEN_ERROR2);
		return (NULL);
	}
	new_cmd_block = create_cmd_block(token_list);
	if (!new_cmd_block)
		return (NULL);
	new_pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new_pipeline)
		exit(EXIT_FAILURE);
	new_pipeline->cmd_block = new_cmd_block;
	new_pipeline->next = NULL;
	return (new_pipeline);
}

int	ft_pipeline_lstsize(t_pipeline *pipeline_lst)
{
	int			cnt;
	t_pipeline	*cur_pipeline;

	cnt = 0;
	cur_pipeline = pipeline_lst;
	while (cur_pipeline)
	{
		cur_pipeline = cur_pipeline->next;
		cnt++;
	}
	return (cnt);
}

t_pipeline	*ft_pipeline_lstlast(t_pipeline *pipeline_lst)
{
	t_pipeline	*cur_pipeline;

	if (!pipeline_lst)
		return (NULL);
	cur_pipeline = pipeline_lst;
	while (cur_pipeline->next)
		cur_pipeline = cur_pipeline->next;
	return (cur_pipeline);
}

void	ft_pipeline_lstadd_back(t_pipeline **pipeline_lst, t_pipeline *new)
{
	t_pipeline	*cur_pipeline;

	if (pipeline_lst == NULL)
		return ;
	if (*pipeline_lst)
	{
		cur_pipeline = ft_pipeline_lstlast(*pipeline_lst);
		cur_pipeline->next = new;
	}
	else
		*pipeline_lst = new;
}

void	ft_pipeline_lstclear(t_pipeline **pipeline_lst)
{
	t_pipeline	*cur_pipeline;
	t_pipeline	*next_pipeline;

	if (*pipeline_lst)
	{
		cur_pipeline = *pipeline_lst;
		while (cur_pipeline)
		{
			next_pipeline = cur_pipeline->next;
			free_cmd_block(cur_pipeline->cmd_block);
			free(cur_pipeline);
			cur_pipeline = next_pipeline;
		}
		*pipeline_lst = 0;
	}
}
