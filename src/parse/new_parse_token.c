
#include "mini_parse.h"

char *get_operator(char *str, size_t *idx)
{
	char	*token_content;
	size_t	len;
	
	len = 1;
	len += (ft_strchr("<>", str[*idx]) && (str[*idx] == str[*idx + len]));
	token_content = ft_substr(str, idx, len);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	*idx += len;
	return (token_content);
}

char *get_word_with_quote(char *str, size_t *idx)
{
	char	open_quote;
	char	*token_content;
	size_t	len;

	open_quote = '\0';
	len = 0;
	while (str[*idx + len])
	{
		if (open_quote == '\0')
		{
			if (is_metacharacter(str[*idx + len]))
				break ;
			else if (is_quote(str[*idx + len]))
				open_quote = str[*idx + len];
		}
		else if (open_quote && open_quote == str[*idx + len])
			open_quote = '\0';
		++len;
	}
	token_content = ft_substr(str, idx, len);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	*idx += len;
	return (token_content);
}

void	create_tokens(t_token **token_list, char *input)
{
	char	*content;
	t_token	*new_token;
	size_t	idx;

	idx = 0;
	while (input[idx])
	{
		while (is_blank(input[idx]))
			idx++;
		if (input[idx] == '\0')
			return ;
		else if (!is_metacharacter(input[idx]))
		{
			content = get_word_with_quote(input, &idx);
			new_token = ft_token_lstnew(WORD, content);
		}
		else if (is_operator_char(input[idx]))
		{
			content = get_operator(input, &idx);
			new_token = ft_token_lstnew(OPERATOR, content);
		}
		if (new_token == NULL)
			exit(EXIT_FAILURE);
		ft_token_lstadd_back(token_list, new_token);
	}
}