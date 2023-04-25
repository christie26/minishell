
#include "mini_parse.h"

char *get_word_without_quote(char **str)
{
	char *substr_offset;
	char open_quote;
	char *token_content;

	open_quote = '\0';
	if (is_quote(**str))
		open_quote = *(*str)++;
	substr_offset = *str;
	while (**str)
	{
		if (open_quote == '\0' && is_quote(**str))
			break;
		else if (open_quote && open_quote == **str)
			break;
		++*str;
	}
	token_content = ft_substr(substr_offset, 0, *str - substr_offset);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	return (token_content);
}

char *get_quote_removed_string(char *str)
{
	t_list *word_list;
	t_list *new_word;
	char *content;

	word_list = NULL;
	while (*str)
	{
		content = get_word_without_quote(&str);
		new_word = ft_lstnew(content);
		if (new_word == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&word_list, new_word);
		// ft_printf("*str: %c\n", *str);
	}
	return (word_list_join(word_list));
}