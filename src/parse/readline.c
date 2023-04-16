
#include "mini_parse.h"

void print_tree(t_pipeline *pipeline_list)
{
	size_t idx = 0;
	while (pipeline_list)
	{
		ft_printf("====================== pipeline %d =======================\n\n", idx++);

		t_cmd_block	*cur_cmd_block = pipeline_list->cmd_block;

		ft_printf("--- redirect ---\n");
		t_redirect	*temp_redir = cur_cmd_block->redirect;
		while (temp_redir)
		{
			ft_printf("\n");
			ft_printf("redirect type: %d\n", temp_redir->type);
			ft_printf("redirect filename: %s\n", temp_redir->filename);
			temp_redir = temp_redir->next;
		}
		ft_printf("\n");

		ft_printf("--- cmd ---\n\n");
		char	**temp_cmd = cur_cmd_block->cmd;
		while (temp_cmd && *temp_cmd) // 이중배열의 NULL 조건을 잘 살펴봐야한다...
		{
			ft_printf("current word: %s\n", *temp_cmd);
			temp_cmd++;
		}

		pipeline_list = pipeline_list->next;
	}
}

int is_blank(char c)
{
	return (c == 32 || c == 9 || c == 10);
}

int is_operator_char(char c)
{
	return (ft_strchr("|&;()<>", c) > 0);
}

int is_metacharacter(char c)
{
	return (is_blank(c) || is_operator_char(c));
}

int is_quote(char c)
{
	return (c == '\'' || c == '\"');
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
	t_list *new_node;

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
	new_node = ft_lstnew(token_str);
	ft_lstadd_back(tokens, new_node);
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

	char *substr_offset;
	char keep_opt;
	char *token_str;
	t_list *new_node;

	substr_offset = *str;
	keep_opt = '\0';
	while (**str)
	{
		if (!is_operator_char(**str)) // 공백은 포함되지 않는다
			break ;
		// 조합가능한지 검사
		// 결과에따라 break ;
		if (keep_opt == '\0')
			keep_opt = **str;
		else if (keep_opt == **str)
		{
			++*str; // substr을 위해 str을 증가시킨다
			break ;
		}
		else
		{
			keep_opt = **str; // 이후의 오퍼레이터와 조합 검사를 위해 keep opt를 갱신, 잘라내는건 이전 문자까지만
			break ;
		}
		++*str;
		// 적어놓고보니 operator는 어차피 많아봤자
		// 한 글자 더 보는건데 while문을 돌리기엔
		// if문이 굉장히 비효율적으로 나온다... (잘 합쳐지지 않는다는 소리)
		// 어차피 과제에서는 redirection operator 만 연속해서 두개받는데...
		// redirection operator, control operator, word 이렇게 구분할까...
	}
	token_str = ft_substr(substr_offset, 0, *str - substr_offset);
	new_node = ft_lstnew(token_str);
	ft_lstadd_back(tokens, new_node);
	return (1);
}

void	create_tokens(t_list **tokens, char *str)
{
	/*

		입력값을 하나씩 순회
		현재 입력이 word인지 operator인지에 따라 get 함수 호출
		get 함수 내에서는 해당 토큰에서 유효한 입력까지만 잘라냄
		str의 주소값을 보내서 get 함수이후에 다음 문자를 볼수있도록 구성

	*/

	while (*str)
	{
		if (is_blank(*str))
			str++;
		else if (is_operator_char(*str))
			get_operator_token(tokens, &str);
		else
			get_word_token(tokens, &str);
	}
}

void print_tokens(void *content)
{
	content = (char *)content;
	ft_putendl_fd(content, 1);
}

t_cmd_block *create_cmd_block(char *str)
{
	t_cmd_block *new_cmd_block;
	t_list *tokens;

	new_cmd_block = (t_cmd_block *)ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		return (NULL);
	create_tokens(&tokens, str);
	ft_lstiter(tokens, print_tokens);
		
	// tokens 해석하며 cmd_block 채워넣기
	// while (tokens)
	// {
	// 	if (ft_strchr("<>", *(char *)tokens->content))
	// 		// create redirect and addback
	// 	else
	// 		// quote remove and cmd addback
	// 	tokens = tokens->next;
	// }

	return (new_cmd_block);
}

void get_redirections(t_list **tokens, t_cmd_block **cmd_block)
{
	t_list *cur_token;
	t_list *next_token;

	if (!tokens || !*tokens)
		return;
	cur_token = *tokens;
	while (cur_token && ((*(char *)(cur_token->content)) != '|')) // 토큰이 다 떨어졌거나 파이프라면 순회 종료
	{
		next_token = cur_token->next;
		if (*((char *)(cur_token->content)) == '<' || *((char *)(cur_token->content)) == '>')
		{
			int type = 0;
			if (ft_strncmp(((char *)(cur_token->content)), "<", 2) == 0)
				type = 1;
			else if (ft_strncmp(((char *)(cur_token->content)), "<<", 2) == 0)
				type = 2;
			else if (ft_strncmp(((char *)(cur_token->content)), ">", 2) == 0)
				type = 3;
			else if (ft_strncmp(((char *)(cur_token->content)), ">>", 2) == 0)
				type = 4;
			
			ft_lstdel_node(tokens, cur_token, free);
			cur_token = next_token;
			next_token = cur_token->next;

			t_redirect *new_redirect = ft_redirect_lstnew(type, (char *)(cur_token->content));
			ft_redirect_lstadd_back(&((*cmd_block)->redirect), new_redirect);

			ft_lstdel_node(tokens, cur_token, NULL); // 문자열은 lstnew에서 써야하니 살려둬야함
			// cur_token = next_token;
			// next_token = cur_token->next;
		}
		cur_token = next_token;
	}
}

void get_cmds(t_list **tokens, t_cmd_block **cmd_block)
{
	size_t cnt = 0;
	size_t idx = 0;
	t_list *cur_token;
	t_list *next_token;

	if (!tokens || !*tokens)
		return;
	cur_token = *tokens;
	while (cur_token && ((*(char *)(cur_token->content)) != '|')) // 토큰이 다 떨어졌거나 파이프라면 순회 종료
	{
		next_token = cur_token->next;
		cnt++;
		cur_token = next_token;
	}

	(*cmd_block)->cmd = (char **)calloc(cnt + 1, sizeof(char *)); // NULL 포인터가 필요한 이중배열이기때문에 +1만큼 생성

	cur_token = *tokens;
	while (idx < cnt)
	{
		next_token = cur_token->next;
		(*cmd_block)->cmd[idx++] = (char *)(cur_token->content);
		ft_lstdel_node(tokens, cur_token, NULL); // 문자열이 cmd안에서 쓰여야 하니 살려둔다
		cur_token = next_token;
	}
}

t_pipeline	*my_parse(char *str)
{
	t_pipeline	*pipe_list = NULL;
	t_list		*tokens = NULL;

	create_tokens(&tokens, str);
	ft_lstiter(tokens, print_tokens);

	(void)(pipe_list);
	// 토큰을 해석하면서 트리에 넣는 함수들
	// 단계별로 함수들이 다름

	// 무조건적으로 토큰화를 하고
	// 1차적으로 토큰을 읽으면서 오류 검사를 할지
	// 토큰화를 하면서 오류 검사를 할지

	if ((*((char *)(tokens->content)) == '|') || (*((char *)(ft_lstlast(tokens)->content)) == '|')) // 첫번째나 마지막이 파이프인 경우 에러
	{
		ft_printf("Error\n");
		exit(1);
	}
	
	while (tokens) // pipe 기준으로 구분되는 pipeline 구조체의 리스트를 만든다
	{
		t_pipeline *new_pipeline;
		t_cmd_block *new_cmd_block;

		new_cmd_block = (t_cmd_block *)ft_calloc(1, sizeof(t_cmd_block));
		get_redirections(&tokens, &new_cmd_block);
		
		get_cmds(&tokens, &new_cmd_block);
		
		new_pipeline = ft_pipeline_lstnew(new_cmd_block);
		ft_pipeline_lstadd_back(&pipe_list, new_pipeline);

		if (tokens && (*(char *)(tokens->content)) == '|')
		{
			t_list *cur_token;
			t_list *next_token;

			cur_token = tokens;
			next_token = cur_token->next;
			ft_lstdel_node(&tokens, cur_token, free);
			cur_token = next_token;
			next_token = cur_token->next;
		}
	}
	return (pipe_list);
}

/*
	파이프 구분이 잘 되었다면
	파이프를 기준으로 앞뒤 문자열을 잘라서
	해당 문자열을 기준으로 하나의 pipe 구조체를 작성
	|| |||| 와 같이 여러 파이프가 연속해서 들어오거나
	" ' 같이 하나의 따옴표만 들어올 경우는 잠시 보류

	해당 문자열에서 리다이렉션이 발견되면 리다이렉션 lst_addback
	그럼 이전에 만든 t_redirection은...? -> 내용부분만 잘라내서 void* content에 넣기
	기존의 lst 타입 활용하면 libft함수를 사용할수있음

	리다이렉션 이외의 문자열은 split을 사용해서 char **로 저장
	리다이렉션들부터 먼저 처리!

	리다이렉션은 (방향) (파일이름) 과 같은 단순한 형태만 우선 고려하기로...
*/
/*
	spilt을 사용해서 pipe단위로 문자열을 긁어냄
	그 char **문자열이 null이 될때까지 순회하며 list 구조체 생성
	pipe 단위에서도 구조체가 그냥 list쓰면 될것같음
	void* content에 cmd_block만 넣기
*/


int main(int argc, char *argv[], char *envp[])
{
    char    *res;
	t_pipeline *pipeline_list;

	(void)argc;
	(void)argv;
	// (void)pipeline_list;
	(void)envp;

    while (1)
    {
		res = readline("yo shell$ ");

		pipeline_list = my_parse(res);
		print_tree(pipeline_list);
		// mini_execute(pipeline_list, envp);

		free(res);
		// while (*res)
			// ft_printf("c: %d\n", *res++);
		// ft_printf("res p: %p\n", res);
    }
}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : cc -lreadline read_line.c && ./a.out

// readline 의 반환값에는 따옴표도 일반적인 문자처럼 포함되어있음
// 기존 쉘에서는 따옴표를 하나의 문장으로 치환해서 해석하지만
// 여기서는 포함된채 통째로 하나의 큰 문자열로 반환해줌
// 모든것이 날것으로 남아있음