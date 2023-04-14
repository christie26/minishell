
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

int is_metacharacter(char c)
{
	return (is_blank(c) || ft_strchr("|&;()<>", c));
}
// get number of tokens 
// white space          ' '
// redirection operator  <, >, <<, >> 
// pipe                  '|'

// operator             &&, ||

int		validate_tokens(t_list *tokens)
{
	char *str;

	str = (tokens->content);
	if (ft_strlen(str) == 1 && ft_strncmp(str, "|", 1) == 0)
		return (0);
	str = ft_lstlast(tokens)->content;
	if (ft_strlen(str) == 1 && ft_strncmp(str, "|", 1) == 0)
		return (0);
	// 파이프로 시작하거나 파이프로 끝나는 경우 에러

	// while (tokens)
	// {
	// 	str = (tokens->content);

	// 	if (ft_strlen(str) == 1)
	// 	{
	// 		if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
	// 		//
	// 	}
	// 	else if (ft_strlen(str) == 2)
	// 	{
	// 		if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
	// 		//
	// 	}

	// 	tokens = tokens->next;
	// }
	return (1);
}

void	create_tokens(t_list **tokens, char *str)
{
	/*

		1. 문자는 공백을 기준으로 분할이됨
		2. 따옴표로 감싸있는 애들은 분할이 진행되지 않음
		3. 문자열끼리 공백없이 함쳐져있으면 하나의 문자열로 인식됨
		4. 리다이렉션 문자가 나오면 리다이렉션 문자만 따로 잘라서 인식 (파이프 포함)
		(리다이렉션이나 파이프같은 오퍼레이터는 따옴표가 없으면 따로 잘라서 인식)
		(하지만 이 오퍼레이터도 따옴표가 더 우선순위가 높음을 주의)
		5. 오퍼레이터가 공백없이 문자 도중에 나오는것도 의식할것

	*/
	
	char *token_str;
	t_list *new_node;

	// while (*str)
	// {
	// 	while (*str == 32 || *str == 9 || *str == 10)
	// 		str++;

	// 	if (*str == '<' || *str == '>')
	// 	{
	// 		if ((*(str + 1) == '<' || *(str + 1) == '>'))
	// 		{
	// 			if (*str == *(str + 1))
	// 			{
	// 				token_str = ft_substr(str, 0, 2);
	// 				str += 2;
	// 			}
	// 			// else
	// 				//error
	// 				// ft_err_msg("Syntax error with <>\n", __FILE__, __LINE__);
	// 		}
	// 		else
	// 		{
	// 			token_str = ft_substr(str, 0, 1);
	// 			str++;
	// 		}

	// 		new_node = ft_lstnew(token_str);
	// 		ft_lstadd_back(tokens, new_node);
	// 	}
	// 	else if (*str == '|')
	// 	{
	// 		// if (*(str + 1) == '|')
	// 			// error
	// 		token_str = ft_substr(str, 0, 1);
	// 		str++;

	// 		new_node = ft_lstnew(token_str);
	// 		ft_lstadd_back(tokens, new_node);
	// 	}
	// 	else
	// 	{
	// 		char *substr_offset = str;
	// 		char open_quote = '\0';

	// 		while (*str != '\0')
	// 		{
	// 			if (*str == '\'' || *str == '\"')
	// 			{
	// 				if (open_quote == '\0')
	// 					open_quote = *str;
	// 				else if (open_quote == *str)
	// 					open_quote = '\0';
	// 			}
	// 			else if (*str == 32 || *str == 9 || *str == 10 || *str == '<' || *str == '>' || *str == '|')
	// 			{
	// 				if (open_quote == '\0')
	// 					break;
	// 			}
	// 			str++;
	// 		}
	// 		token_str = ft_substr(substr_offset, 0, str - substr_offset);
	// 		new_node = ft_lstnew(token_str);
	// 		ft_lstadd_back(tokens, new_node);
	// 	}
	// }
	
	int is_opt = 0;
	while (*str)
	{
		/*

			if *str == opt
				if is_opt
					str++
				else
					is_opt = 1;
				- 오퍼레이터를 읽고있었다면 계속 읽는다
				- 그렇지 않으면 플래그를 세우고 조건문을 다시 한바퀴 돌린다
			else
				if is_opt
					is_opt = 0;
				else
					str++
				- 문자를 읽고있었다면 계속 읽는다
				- 그렇지 않으면 플래그를 세우고 조건문을 다시 한바퀴 돌린다
			
			이렇게 하면 플래그에 따라서 읽었던것까지 잘라주고
			다른 타입의 토큰이 나와도 무조건적으로 다음 문자를 보지않게된다
			다른 타입의 토큰이 나올때 예외처리를 신경쓰지 않아도 된다
			그냥 플래그를 확인하고 플래그에 따른 동작만 수행한다

			is_opt는 플래그 역할도 수행하지만 이전에 읽은 opt에 대한
			정보를 담는 역할도 한다

		*/
		char *substr_offset = str;

		if (is_metacharacter(*str))
		{
			if (is_opt)
			{
				// 조합 가능한 오퍼레이터인지 검사
				// 더이상 조합가능하지 않으면 읽었던 오퍼레이터까지 토큰화하고 is_opt 갱신
				// 조합이 가능하면 조합하고 is_opt를 0으로 초기화
				if (ft_strchr("<>", is_opt))
				{
					if (is_opt == *str)
					{
						is_opt = 0;

						token_str = ft_substr(substr_offset, 0, str - substr_offset + 1);
						new_node = ft_lstnew(token_str);
						ft_lstadd_back(tokens, new_node);
					}
					else
					{
						is_opt = *str;

						// token_str = ft_substr(substr_offset, 0, str - substr_offset);
						// 이 상태에서는 자기자신 하나만 잘라내는것이 불가능해진다...
						token_str = ft_substr(substr_offset, 0, str - substr_offset + 1);
						new_node = ft_lstnew(token_str);
						ft_lstadd_back(tokens, new_node);
					}
					// <>a 는 <, >, a 세개의 토큰으로 나뉘어야 한다
					// <a 는 <, a 두개의 토큰으로 나뉘어야 한다
					// 플래그 반전이나 널문자가 나올때 잘라내야 하나?
					//
					// 조합이 가능하면 현재 문자까지 포함해서 자른다
					// 조합이 불가능하면 이전 문자까지만 자른다?
					// 그러면 실패한 경우 or 변수에 킵 해놓는 경우는 한글자가 늦게 잘리나?
					//
					// 킵 해놓는 이유 -> 플래그로도 사용하기 위해서
					//
					// 아무튼 같아도 자르고 달라도 자르고...
					// 여러 오퍼레이션이 연속해서 들어오는 경우는 어떻게 처리하는지? <- 결국 이거때문에
					// 킵 해놓은 거랑 비교해보는것 아닌가??
					// 매번 한글자씩 밀려서 자르다가 플래그 반전이 일어나면
					// 그떄 킵해놨던 오퍼레이터를 토큰화?
					// 문자는 킵해놓을 이유가 없음 그냥 문자열 주소를 쭉쭉 밀어버리면 됨
					//
					// 그러나 오퍼레이터는 조합도 봐야하고
					// 오퍼레이터 자체도 플래그라서 계속 확인해야함
					// 오퍼레이터 쪽에서 플래그 반전이나 널문자를 만나기전까진
					// 킵해놓는것 때문에 하나씩 밀려서 잘리는건 당연한것
					// 다만 오퍼레이터에서 word 로 바뀔때만 킵해놓은것을 자르는게 일어남
					// 그 반대는 현재까지 보고있는 문자까지 바로 잘라버림
				}
				str++;
				// 인덱스를 늘리는 타이밍과 여태까지 인덱스를 잘라내는 타이밍의 차이는...?
				// 과제 요구사항으로는 같은 오퍼레이터 두개까지만 조합을 확인하면 된다
				// 플래그 반전이 일어나서 끊고가는것처럼 조합도 같은 타이밍에 끊고가면 되지 않을까
				// 문자열 밀어주기가 끝날때 잘라내면 플래그 반전에도 대응할수있지 않을까...
			}
			else if (is_opt == 0)
			{
				is_opt = *str;
				// 플래그 반전
				// 이전까지 읽었던 문자까지 토큰화
			}
		}
		else
		{
			if (is_opt)
				is_opt = 0;
			else
				str++;
		}
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
	// ft_lstiter(tokens, print_tokens);

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
	(void)envp;
	// (void)pipeline_list;

    while (1)
    {
		res = readline("yo shell$ ");

		pipeline_list = my_parse(res);
		print_tree(pipeline_list);
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