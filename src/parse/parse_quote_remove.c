
#include "mini_parse.h"

/*
	공백을 제외하고 모든 문자를 하나의 토큰으로 생성한다
	나중에 트리화 하는 과정에서 첫단계에 operator로 나누어진 토큰인지
	word 안에서 확장으로 생성된 operator 문자인지는 구분할수없다는 문제가 있음
*/
char *get_word_with_operator(char **word)
{
	char *substr_offset;
	char open_quote;
	char *token_content;

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

/*
	content의 추가분할을 시도한다
	맨 처음 토큰화와는 다르게 공백만 구분자로 사용된다
*/
void word_splitting(t_token **new_list, char *word)
{
	char	*cur_content;
	char	*new_content;
	t_token	*new_token;

	cur_content = word;
	while (*cur_content)
	{
		while (is_blank(*cur_content))
			cur_content++;
		if (*cur_content == '\0')
			return ;
		new_content = get_word_with_operator(&cur_content);
		new_token = ft_token_lstnew(WORD, new_content);
		if (new_token == NULL)
			exit(EXIT_FAILURE);
		ft_token_lstadd_back(new_list, new_token);
	}
}

/*
	모든 토큰을 순회하며 추가로 분할을 시도한다
	무조건 기존의 content를 교체한다
	토큰수에 변동이 있을경우 중간에 삽입하되
	추가된 토큰에 대한 확장검사는 진행되지 않는다
*/
void splitting_tokens(t_token **token_list)
{
	t_token *new_list;
	t_token *cur_token;
	t_token *next_token;

	cur_token = *token_list;
	while (cur_token)
	{
		next_token = cur_token->next; // 원래 next node 를 저장해두고
		new_list = NULL;
		word_splitting(&new_list, cur_token->value); // 추가 분할을 시도한 새 리스트를 생성
		if (new_list == NULL)
			ft_token_lstdel_node(token_list, cur_token);
		else
		{
			free(cur_token->value);
			cur_token->value = new_list->value; // 기존의 content 교체
			if (new_list->next) // 추가적인 분할로인해 새로운 노드가 생성되었다면
			{
				cur_token->next = new_list->next; // 새 리스트의 두번째 노드부터 이어붙인다
				ft_token_lstlast(cur_token)->next = next_token; // 그리고 저장해둔 next node 를 다시 이어붙인다
			}
			free(new_list);
		}
		cur_token = next_token;
	}
}

/*
	토큰을 순회하며 주어진 토큰의 content를
	따옴표가 제거된 content로 교체한다
*/
void quote_remove_tokens(t_token **token_list)
{
	t_token *cur_token;
	char *content;

	cur_token = *token_list;
	while (cur_token)
	{
		content = get_quote_removed_string(cur_token->value);
		if (content == NULL)
		{
			ft_token_lstclear(token_list);
			return;
		}
		free(cur_token->value);
		cur_token->value = content;
		cur_token = cur_token->next;
	}
}

/*
	따옴표 또한 구분자로 취급하여 문자열을 생성한다
*/
char *get_word_without_quote(char *str, size_t *idx)
{
	char *token_content;
	char open_quote;
	size_t len;

	len = 0;
	open_quote = 0;
	if (is_quote(str[*idx]))
		open_quote = str[(*idx)++];
	while (str[*idx + len])
	{
		if (open_quote && open_quote == str[*idx + len])
			break;
		if (open_quote == 0 && is_quote(str[*idx + len]))
			break;
		++len;
	}
	if (open_quote && open_quote != str[*idx + len])
		return (NULL);
	token_content = ft_substr(str, *idx, len);
	if (token_content == NULL)
		exit(EXIT_FAILURE);
	*idx += len + (open_quote != 0);
	return (token_content);
}

/*
	따옴표를 플래그 및 구분자로 사용하여
	부분 문자열들을 생성하고
	일괄적으로 합쳐서 반환한다
*/
char *get_quote_removed_string(char *str)
{
	t_list *word_list;
	t_list *new_word;
	char *content;
	size_t idx;

	word_list = NULL;
	idx = 0;
	while (str[idx])
	{
		content = get_word_without_quote(str, &idx);
		if (content == NULL) // 따옴표가 닫히지 않음
		{
			ft_printf("yo shell: quote not closed\n");
			ft_lstclear(&word_list, free);
			return (NULL);
		}
		new_word = ft_lstnew(content);
		if (new_word == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&word_list, new_word);
	}
	return (word_list_join(word_list));
}
