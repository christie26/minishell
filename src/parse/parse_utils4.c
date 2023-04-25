
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
		tokens = tokens->next;
	}

	// 같은 토큰을 그대로 검사하면 토큰을 확장했을때
	// 확장한 값에 $변수이름 이 존재할경우 중복해서 확장해버림...
	// 이 부분도 순서대로 앞에서 읽어나가면서 한번씩만 처리하도록 해야할듯
	// 거의 모든 연산들이 한글자씩 순서대로 읽어나가면서 처리하는듯한 그림이 그려진다
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

char *get_expanded_string(char *str, char **my_env)
{
	/*

		확장여부에 따라 플래그처럼 작동
		확장 이전, 확장, 확장이전, 확장 ...
		부분 문자열들을 리스트로 생성
		리스트를 순회하며 하나로 합치는 함수는 따로 작성

	*/

	t_list *word_list;
	char open_quote;
	char *substr_offset;

	word_list == NULL;
	substr_offset = str;
	open_quote = '\0';

	// 확장이 아닌 부분문자열을 만드는 부분
	// ------------------
	
	while (*str)
	{
		if (!open_quote && is_quote(*str))
			open_quote = *str;
		else if (open_quote && open_quote == *str)
			open_quote = '\0';
		if (*str == '$' && open_quote != '\'')
			break;
		str++;
	}
	char *word = ft_substr(substr_offset, 0, str - substr_offset);
	if (word == NULL)
		exit(EXIT_FAILURE);
	t_list *new_word = ft_lstnew(word);
	if (new_word == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(&word_list, new_word);
	// ------------------


	// $를 만나고, 작은 따옴표로 열려있지 않은 상태 
	if (*str == '$' && open_quote != '\'')
		change_to_value(my_env);	
	// get_key - 뭐가 뽑혀나왔다 -> get_value의 반환값으로 리스트를 만들어서 추가
	// 키가 뽑혀나온게 없으면 -> 그냥 리터럴로 출력해야하니까 -> 부분 문자열로 만들어서 추가
	// 중괄호가 있다면 키값의 유효성을 검사하겠지만 중괄호가 없다면  get_key에 문자열을 반환받을것임
	// ------------------


	while(*str)
	{
		if (expanable() && get_key())
			content = get_value();
		else
			content = get_substring();
		new_token = ft_lstnew(content);
		if (new_token == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(tokens, new_token);
	}
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
}

char *get_expanded_string(char *str, char **my_env)
{
	t_list *word_list;
	t_list *new_word;
	char *content;
	char *result;

	word_list = NULL;
	while (*str)
	{
		if (*str != '$' && get_key_from_word(str))
			content = get_expanded_word(&str);
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