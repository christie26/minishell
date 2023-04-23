
#include "mini_parse.h"

int is_blank(char c)
{
	return (c == 32 || c == 9 || c == 10);
}

int is_operator_char(char c)
{
	return (ft_strchr("|<>", c) > 0);
}

int is_metacharacter(char c)
{
	return (is_blank(c) || is_operator_char(c));
}

int is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
