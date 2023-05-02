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

char	*get_key_from_word(char **str)
{
	int		brace;
	char	*substr_offset;
	char	*key;

	brace = (**str == '{');
	if (brace)
		++*str;
	substr_offset = *str;
	while (ft_isalnum(**str))
		++*str;
	if (brace)
	{
		if (**str == '\0')
			ft_printf("yo shell: brace not closed\n");
		else if (**str != '}' || *str - substr_offset == 0)
			ft_printf("yo shell: bad substitution\n");
		return (NULL);
	}
	key = ft_substr(substr_offset, 0, *str - substr_offset);
	if (key == NULL)
		exit(EXIT_FAILURE);
	if (brace)
		++*str;
	return (key);
}

char	*get_expanded_word(char **str, char **my_env)
{
	char	check;
	char	*key;
	char	*result;

	check = *(*str + 1);
	if (ft_isalnum(check) || check == '{')
	{
		++*str;
		key = get_key_from_word(str);
		if (key == NULL)
			return (NULL);
		result = get_value(key, my_env);
		free(key);
		return (result);
	}
	else if (check == '?')
	{
		++*str;
		++*str;
		return (get_value("?", my_env));
	}
	else
	{
		if (is_quote(check))
			++*str;
		return (get_non_expanded_word(str));
	}
}

char	*get_non_expanded_word(char **str)
{
	char	open_quote;
	char	*substr_offset;
	char	*word;

	substr_offset = *str;
	open_quote = '\0';
	if (**str == '$')
		++*str;
	while (**str)
	{
		if (!open_quote && is_quote(**str))
			open_quote = **str;
		else if (open_quote && open_quote == **str)
			open_quote = '\0';
		if (**str == '$' && open_quote != '\'')
			break ;
		++*str;
	}
	word = ft_substr(substr_offset, 0, *str - substr_offset);
	if (word == NULL)
		exit(EXIT_FAILURE);
	return (word);
}

char	*get_expanded_string(char *str, char **my_env)
{
	t_list	*word_list;
	t_list	*new_word;
	char	*content;

	word_list = NULL;
	while (*str)
	{
		if (*str == '$')
		{
			content = get_expanded_word(&str, my_env);
			if (content == NULL)
			{
				ft_lstclear(&word_list, free);
				return (NULL);
			}
		}
		else
			content = get_non_expanded_word(&str);
		new_word = ft_lstnew(content);
		if (new_word == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&word_list, new_word);
	}
	return (word_list_join(word_list));
}
