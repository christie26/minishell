
#include "mini_parse.h"

void print_tokens(void *content)
{
	content = (char *)content;
	ft_putendl_fd(content, 1);
}

int		get_word_token(t_list **tokens, char **str)
{
	/*

		호출조건
		- 메타캐릭터가 아닐것
		- 널문자가 아닐것

	*/

	char *substr_offset;
	char open_quote;
	char *token_str;
	t_list *new_token;

	substr_offset = *str;
	open_quote = '\0';
	while (**str)
	{
		if (open_quote == '\0')
		{
			if (is_metacharacter(**str))
				break ;
			else if (is_quote(**str))
				open_quote = **str;
		}
		else if (open_quote && open_quote == **str)
			open_quote = '\0';
		++*str;
	}
	token_str = ft_substr(substr_offset, 0, *str - substr_offset);
	new_token = ft_lstnew(token_str);
	ft_lstadd_back(tokens, new_token);
	return (1);
}

int get_operator_token(t_list **tokens, char **str)
{
	/*

		호출조건
		- 메타캐릭터일것
		- 따옴표가 아닐것
		- 널문자가 아닐것

	*/

	char	*substr_offset;
	char	*token_str;
	t_list	*new_token;
	
	substr_offset = *str;
	++*str;
	if (**str && (*(*str - 1) == **str && ft_strchr("<>", **str)))
		++*str;
	token_str = ft_substr(substr_offset, 0, *str - substr_offset);
	new_token = ft_lstnew(token_str);
	ft_lstadd_back(tokens, new_token);
	return (1);
}

/*

	따옴표가 열려있으면 짝맞추기를 안해도됨?
	말그대로 리터럴이 되어버리고
	따옴표 안에서는 특별한 의미를 잃어버리기 때문 -> 확장포함
	그럼 확장의 주도권을 따옴표 제거가 가져야 하나?

*/

void	create_tokens(t_list **tokens, char *str)
{
	while (*str)
	{
		if (!is_metacharacter(*str))
			get_word_token(tokens, &str);
		else if (is_operator_char(*str))
			get_operator_token(tokens, &str);
		else
			str++;
	}
}
