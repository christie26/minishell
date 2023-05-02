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
