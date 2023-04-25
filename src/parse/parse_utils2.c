
#include "mini_parse.h"

void print_tokens(void *content)
{
	content = (char *)content;
	ft_putendl_fd(content, 1);
}

char *get_operator(char **input)
{
	char	*substr_offset;
	char	*token_content;
	
	substr_offset = *input;
	++*input;
	if (**input && (*(*input - 1) == **input && ft_strchr("<>", **input)))
		++*input;
	token_content = ft_substr(substr_offset, 0, *input - substr_offset);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	return (token_content);
}

char *get_word_with_quote(char **input)
{
	char *substr_offset;
	char open_quote;
	char *token_content;

	substr_offset = *input;
	open_quote = '\0';
	while (**input)
	{
		if (open_quote == '\0')
		{
			if (is_metacharacter(**input))
				break ;
			else if (is_quote(**input))
				open_quote = **input;
		}
		else if (open_quote && open_quote == **input)
			open_quote = '\0';
		++*input;
	}
	token_content = ft_substr(substr_offset, 0, *input - substr_offset);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	return (token_content);
}

char *get_word_without_quote(char **input)
{
	char *str;
	char open_quote;
	char *token_content;

	size_t len;

	str = *input;
	open_quote = '\0';
	len = 0;
	while (*str)
	{
		if ((open_quote == '\0' && ft_isalnum(*str)) || open_quote) // 순수문자거나 인용문이거나
			len++;
		else if (is_quote(*str)) // 따옴표 처리
		{
			if (open_quote == '\0')
				open_quote = *str;
			else if (open_quote == *str)
				open_quote = '\0';
		}
		else // 결과물에 들어가는 문자가 아닌경우
			break ;
		++str;
	}
	
	token_content = ft_calloc(1, len);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	
	open_quote = '\0';
	while (**input)
	{
		if ((open_quote == '\0' && ft_isalnum(**input)) || open_quote) // 순수문자거나 인용문이거나
			*token_content++ = **input;
		else if (is_quote(**input)) // 따옴표 처리
		{
			if (open_quote == '\0')
				open_quote = **input;
			else if (open_quote == **input)
				open_quote = '\0';
		}
		else // 결과물에 들어가는 문자가 아닌경우
			break ;
		++*input;
	}
	
	return (token_content);
}

void	create_tokens(t_list **tokens, char *input)
{
	t_list *new_token;

	while (*input)
	{
		while (is_blank(*input))
			input++;
		if (!is_metacharacter(*input))
		{
			new_token = ft_lstnew(get_word_with_quote(*input));
			if (new_token == NULL)
				exit(EXIT_FAILURE);
			ft_lstadd_back(tokens, new_token);
		}
		else if (is_operator_char(*input))
		{
			new_token = ft_lstnew(get_operator(*input));
			if (new_token == NULL)
				exit(EXIT_FAILURE);
			ft_lstadd_back(tokens, new_token);
		}
	}
}