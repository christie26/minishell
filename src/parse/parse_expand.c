
#include "mini_parse.h"

void expand_tokens(t_list *tokens, char** my_env)
{
	int is_here_doc;
	char *content;

	is_here_doc = 0;
	while (tokens)
	{
		if (is_operator_char(*(char *)(tokens->content)) || is_here_doc)
		{
			is_here_doc = (ft_strcmp(tokens->content, "<<") == 0);
			tokens = tokens->next;
			continue;
		}
		content = get_expanded_string(tokens->content, my_env);
		if (content == NULL) // bad substitution
		{
			ft_lstclear(&tokens, free);
			return;
		}
		free(tokens->content);
		tokens->content = content;
		tokens = tokens->next;
	}
}

char *word_list_join(t_list *word_list)
{
	char *result;
	char *temp;
	t_list *word_list_iter;

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

char *get_key_from_word(char **str)
{
	// 중괄호 사용여부 체크
	// 중괄호를 사용했다면 bad substitution 체크
	// 그렇지 않으면 ft_alnum일때만 계속해서 변수이름으로 해석한다
	int brace;
	char *substr_offset;
	char *key;

	brace = (**str == '{');
	if (brace)
		++*str;
	substr_offset = *str;
	while (ft_isalnum(**str))
		++*str;
	if (brace)
	{
		if (**str == '\0')
			ft_printf("brace not closed\n");
		else if (**str != '}')
			ft_printf("bad substitution\n");
		return (NULL);
	}
	key = ft_substr(substr_offset, 0, *str - substr_offset);
	if (key == NULL)
		exit(EXIT_FAILURE);
	if (brace)
		++*str;
	return (key);
}

char *get_expanded_word(char **str, char **my_env)
{
	char check;
	char *key;
	char *result;

	check = *(*str + 1); // 체크할때는 문자 주소가 밀리면 안된다, 맨 마지막 케이스에서 $를 포함해서 단어를 만들어야하기 때문에
	if (ft_isalnum(check) || check == '{')
	{
		++*str;
		key = get_key_from_word(str);
		if (key == NULL) // bad substitution or not closed brace
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
	else // 문자열 확장이거나 의미없는 특수문자인경우 $포함해서 그냥 출력
	{
		if (is_quote(check))
			++*str; // 따옴표라면 $빼고 따옴표부터
		return (get_non_expanded_word(str));
	}
}

char *get_non_expanded_word(char **str)
{
	char open_quote;
	char *substr_offset;
	char *word;

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
			break;
		++*str;
	}
	word = ft_substr(substr_offset, 0, *str - substr_offset);
	if (word == NULL)
		exit(EXIT_FAILURE);
	return (word);
}

char *get_expanded_string(char *str, char **my_env)
{
	t_list *word_list;
	t_list *new_word;
	char *content;

	word_list = NULL;
	while (*str)
	{
		if (*str == '$')
		{
			content = get_expanded_word(&str, my_env);
			if (content == NULL) // bad substitution or not closed brace
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