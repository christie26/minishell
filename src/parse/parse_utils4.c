
#include "mini_parse.h"

/*

	is_expandable -  확장가능한 부분이 있는지 문법검사 수행
	if ture
	$ 문자를 찾아서 해당 문자 이전까지 substr로 저장 (s1, pre_word)
	$ 문자 이후로 키값이 되는 부분을 읽어냄, value를 문자열 변수에 저장 (s2, expanded_word) -> 문자열값은 증가되어있음
	키값 이후 (괄호까지 밀어낸)의 문자열을 substr로 저장 (s3, post_word)
	이 세개의 문자열을 순서대로 strjoin으로 합침
	맨위로 돌아가서 다시 확장가능한지 검사, 반복

	더이상 확장이 불가능하면 다음 토큰으로 이동하여 검사

*/

int	is_expandable(char *word)
{
	char *check;
	int open_quote;
	
	check = word;
	open_quote = 0;
	while (*check)
	{
		if (is_quote(*check))
		{
			if (open_quote && open_quote == *check)
				open_quote = 0;
			else if (!open_quote)
				open_quote = *check;
		}
		else if (*check == '$' && (!open_quote || open_quote == '\"'))
		{
			if (*(check + 1) && (ft_isalnum(*(check + 1)) || *(check + 1) == '{'))
				return (1);
		}
		check++;
	}
	return (0);
}

void expand_check(t_list *tokens, char **my_env)
{
	char *pre_word;
	char *expanded_word;
	char *post_word;
	char *substr_offset;

	while (tokens)
	{
		while (is_expandable(tokens->content))
		{
			char *word = tokens->content;

			substr_offset = word;
			word = ft_strchr(word, '$');
			pre_word = ft_substr(substr_offset, 0, word - substr_offset);

			int brace = (*(++word) == '{');
			word += brace;
			substr_offset = word;
			
			while (ft_isalnum(*word))
				word++;

			if (brace && (*word != '}' || word - substr_offset == 0))
			{
				free(pre_word);
				ft_printf("bad substitution\n");
				exit(1);
			}
			
			char *key = ft_substr(substr_offset, 0, word - substr_offset);
			expanded_word = get_value(key, my_env);
			free(key);
			
			if (!expanded_word)
				expanded_word = ft_strdup("");

			word += brace;
			substr_offset = word;
			while (*word)
				word++;
			post_word = ft_substr(substr_offset, 0, word - substr_offset);

			char *result = ft_strjoin(pre_word, expanded_word);
			result = ft_strjoin(result, post_word);

			free(pre_word);
			free(expanded_word);
			free(post_word);

			free(tokens->content);
			tokens->content = result;
			
		}
		tokens->content = quote_removal(tokens->content);
		tokens = tokens->next;
	}

	// 같은 토큰을 그대로 검사하면 토큰을 확장했을때
	// 확장한 값에 $변수이름 이 존재할경우 중복해서 확장해버림...
	// 이 부분도 순서대로 앞에서 읽어나가면서 한번씩만 처리하도록 해야할듯
	// 거의 모든 연산들이 한글자씩 순서대로 읽어나가면서 처리하는듯한 그림이 그려진다
}

char *quote_removal(char *str)
{
	/*
	
		export a="123 456""789 abc"

		cat $a -> cat 123 456789 abc
		cat "$a" -> cat "123 456789 abc"

		마지막에 표시할때도 가장 겉의 따옴표를 없애야 하는데
		입력받을때도 따옴표로 붙어있던애들은 같이 받아줘야함...
		대체 어느타이밍에서 따옴표를 지워야 하는지?

	*/

	char open_quote;
	size_t len = 0;

	open_quote = 0;
	char *serch = str;

	while (*serch)
	{
		if (!open_quote && is_blank(*serch))
			break;
		else if (!open_quote && is_quote(*serch))
		{
			open_quote = *serch;
			serch++;
		}
		else if (open_quote && (open_quote == *serch))
		{
			open_quote = 0;
			serch++;
		}
		else
		{
			len++;
			serch++;
		}
	}

	char *result = ft_calloc(1, len + 1);

	open_quote = 0;
	serch = str;
	char *result_ptr = result;

	while (*serch)
	{
		if (!open_quote && is_blank(*serch))
			break;
		else if (!open_quote && is_quote(*serch))
		{
			open_quote = *serch;
			serch++;
		}
		else if (open_quote && (open_quote == *serch))
		{
			open_quote = 0;
			serch++;
		}
		else
			*result_ptr++ = *serch++;
	}
	
	return (result);
}