#include "mini_parse.h"

char	*get_word_with_operator(char **word)
{
	char	*substr_offset;
	char	open_quote;
	char	*token_content;

	substr_offset = *word;
	open_quote = '\0';
	while (**word)
	{
		if (open_quote == '\0')
		{
			if (is_blank(**word))
				break ;
			else if (is_quote(**word))
				open_quote = **word;
		}
		else if (open_quote && open_quote == **word)
			open_quote = '\0';
		++*word;
	}
	token_content = ft_substr(substr_offset, 0, *word - substr_offset);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	return (token_content);
}

void	word_splitting(t_token **new_list, char *word)
{
	char	*cur_content;
	char	*new_content;
	t_token	*new_token;

	cur_content = word;
	while (*cur_content)
	{
		while (is_blank(*cur_content))
			cur_content++;
		if (*cur_content == '\0')
			return ;
		new_content = get_word_with_operator(&cur_content);
		new_token = ft_token_lstnew(WORD, new_content);
		if (new_token == NULL)
			exit(EXIT_FAILURE);
		ft_token_lstadd_back(new_list, new_token);
	}
}

void	splitting_tokens(t_token **token_list)
{
	t_token	*new_list;
	t_token	*cur_token;
	t_token	*next_token;

	cur_token = *token_list;
	while (cur_token)
	{
		next_token = cur_token->next;
		new_list = NULL;
		word_splitting(&new_list, cur_token->value);
		if (new_list == NULL)
			ft_token_lstdel_node(token_list, cur_token);
		else
		{
			free(cur_token->value);
			cur_token->value = new_list->value;
			if (new_list->next)
			{
				cur_token->next = new_list->next;
				ft_token_lstlast(cur_token)->next = next_token;
			}
			free(new_list);
		}
		cur_token = next_token;
	}
}

void	quote_remove_tokens(t_token **token_list)
{
	t_token	*cur_token;
	char	*content;

	cur_token = *token_list;
	while (cur_token)
	{
		content = get_quote_removed_string(cur_token->value);
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

char	*get_word_without_quote(char *str, size_t *idx)
{
	char	*token_content;
	char	open_quote;
	size_t	len;

	len = 0;
	open_quote = 0;
	if (is_quote(str[*idx]))
		open_quote = str[(*idx)++];
	while (str[*idx + len])
	{
		if (open_quote && open_quote == str[*idx + len])
			break ;
		if (open_quote == 0 && is_quote(str[*idx + len]))
			break ;
		++len;
	}
	if (open_quote && open_quote != str[*idx + len])
		return (NULL);
	token_content = ft_substr(str, *idx, len);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	*idx += len + (open_quote != 0);
	return (token_content);
}

char	*get_quote_removed_string(char *str)
{
	t_list	*word_list;
	t_list	*new_word;
	char	*content;
	size_t	idx;

	word_list = NULL;
	idx = 0;
	while (str[idx])
	{
		content = get_word_without_quote(str, &idx);
		if (content == NULL)
		{
			ft_printf("yo shell: quote not closed\n");
			ft_lstclear(&word_list, free);
			return (NULL);
		}
		new_word = ft_lstnew(content);
		if (new_word == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&word_list, new_word);
	}
	return (word_list_join(word_list));
}
