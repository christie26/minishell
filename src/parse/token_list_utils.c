#include "mini_parse.h"

t_token	*ft_token_lstnew(int type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

t_token	*ft_token_lstlast(t_token *token_lst)
{
	t_token	*cur_token;

	if (!token_lst)
		return (NULL);
	cur_token = token_lst;
	while (cur_token->next)
		cur_token = cur_token->next;
	return (cur_token);
}

void	ft_token_lstadd_back(t_token **token_lst, t_token *new)
{
	t_token	*cur_token;

	if (token_lst == NULL)
		return ;
	if (*token_lst)
	{
		cur_token = ft_token_lstlast(*token_lst);
		cur_token->next = new;
	}
	else
		*token_lst = new;
}

void	ft_token_lstdel_node(t_token **token_lst, t_token *target)
{
	t_token	*prev_node;
	t_token	*cur_node;

	prev_node = NULL;
	cur_node = *token_lst;
	while (cur_node != target)
	{
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
	if (prev_node == NULL)
		*token_lst = cur_node->next;
	else
		prev_node->next = cur_node->next;
	free(cur_node->value);
	free(cur_node);
	return ;
}

void	ft_token_lstclear(t_token **token_lst)
{
	t_token	*cur_token;
	t_token	*next_token;

	if (*token_lst)
	{
		cur_token = *token_lst;
		while (cur_token)
		{
			next_token = cur_token->next;
			free(cur_token->value);
			free(cur_token);
			cur_token = next_token;
		}
		*token_lst = 0;
	}
}
