
#include "mini_parse.h"

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

	// 따옴표 제거는 here_doc에도 적용됨
	
}

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