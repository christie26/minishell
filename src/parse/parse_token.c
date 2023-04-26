
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

void	create_tokens(t_list **tokens, char *input)
{
	char	*content;
	t_list	*new_token;

	while (*input)
	{
		while (is_blank(*input))
			input++;
		if (*input == '\0')
			break;
		else if (!is_metacharacter(*input))
			content = get_word_with_quote(&input);
		else if (is_operator_char(*input))
			content = get_operator(&input);
		new_token = ft_lstnew(content);
		if (new_token == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(tokens, new_token);
	}
}