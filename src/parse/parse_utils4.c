
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

void quote_remove_check(t_list *tokens)
{
	while (tokens)
	{
		quote_removal(tokens);
		tokens = tokens->next;
	}
}

void quote_removal(t_list *token)
{
	char *str = token->content;
	char open_quote;
	
	open_quote = 0;
	char *serch = str;
	int word_cnt = 0;

	while (*serch && !open_quote && is_blank(*serch))
		serch++;
	while (*serch)
	{
		while (*serch && (open_quote || !is_blank(*serch)))
		{
			if (!open_quote && is_quote(*serch))
				open_quote = *serch;
			else if (open_quote && (open_quote == *serch))
				open_quote = 0;
			serch++;
		}
		while (*serch && !open_quote && is_blank(*serch))
			serch++;

		word_cnt++;
	}
	// ft_printf("word cnt: %d\n", word_cnt);

	//-------------------

	char **words = malloc(sizeof(char *) * word_cnt);

	size_t len;
	int i = 0;

	
	while (i < word_cnt)
	{
		serch = str;
		len = 0;
		open_quote = 0;
		
		while (*serch && (!open_quote && is_blank(*serch)))
			serch++;
		
		while (*serch)
		{
			while (*serch && (!open_quote && is_blank(*serch)))
				break;
			
			if (!open_quote && is_quote(*serch))
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
		char *result_ptr = result;

		while (*str && (!open_quote && is_blank(*serch)))
			str++;
		
		while (*str)
		{
			if (!open_quote && is_blank(*str))
				break;
			else if (!open_quote && is_quote(*str))
			{
				open_quote = *str;
				str++;
			}
			else if (open_quote && (open_quote == *str))
			{
				open_quote = 0;
				str++;
			}
			else
				*result_ptr++ = *str++;
		}

		words[i] = result;
		// ft_printf("words[%d]: %s\n", i, words[i]);
		++i;

		while (*str && (!open_quote && is_blank(*str)))
			str++;
	}

	// free(token->content);
	token->content = words[0];

	if (word_cnt > 1)
	{
		i = 1;
		while (i < word_cnt)
		{
			t_list *next_token = token->next;
			t_list *new_token;
			new_token = ft_lstnew(words[i++]);
			token->next = new_token;
			new_token->next = next_token;
			token = new_token;
		}
	}

	/*
	
		아직은 따옴표 제거도중 하나의 단어만 골라내게 만듬
		따옴표 제거후 여러 토큰으로 나뉜다면 어떤식으로 추가수정할것인지?
		우선 get_word_token의 활용방안을 모색한다

		node1 - node2 - node3

		위와 같은 구조에서 node2에서 따옴표 제거가 이루어지고
		토큰의 수에 변동이 생겼다고 가정한다면 (word splitting)
		
		node1 - node2 (word1) (word2) (word3) - node3

		node2의 content는 word1가 대체하고
		추가로 word가 필요한만큼 node들을 만들어서 연결후
		node2의 next 였던 node3를 잘 연결시켜준다...?

		node1 - node2 - word2 - word3 - node3

		그냥 get_word_token써서 리스트 쭉 뽑아내고
		첫번째꺼만 content 교체후 free하고 나머지는 이어붙여주기? <-- 이게 더 나아보임
		content 교체후 next가 null인지 체크하면 될것같음

		get_word_token은 따옴표를 제거하지 않는다...

	*/
	
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
	if (!(brace && **str == '}'))
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
		ft_printf("check: %c\n", check);
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
		return (get_non_expanded_word(str));

}

char *get_non_expanded_word(char **str)
{
	char open_quote;
	char *substr_offset;
	char *word;

	substr_offset = *str;
	open_quote = '\0';
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
	/*
		while (*str)
		{
			if 확장가능성이 있다 && 키값이 유효하다 -> get_key()
				substr = get_value, 문자열은 주소 밀려서 나옴
			else
				substr = 일반 부분문자열로 해석해서 만든다, 문자열은 주소 밀려서 나옴
			lstaddback = lstnew(substr);
		}
		리스트 순회하면서 다 이어붙이기
		반환
	*/

	t_list *word_list;
	t_list *new_word;
	char *content;
	char *result;

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
				// bad substitution 처리
				// malloc 에러는 안에서 exit를 해버리기 떄문
		}
		else
			content = get_non_expanded_word(&str);
		new_word = ft_lstnew(content);
		if (new_word == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&word_list, new_word);
	}
	result = word_list_join(word_list);
	return (result);
}