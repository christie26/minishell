
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

void expand_from_env(char **str)
{
	char *var_key;
	char *substr_offset;

	var_key = ft_strchr(*str, '$');
	while (var_key)
	{
		substr_offset = ++var_key;
		while (ft_isalpha(*var_key))
			var_key++;
		var_key = ft_strchr(*str, '$');
	}
}

void expand_check(t_pipeline *pipeline_list)
{
	t_cmd_block *cur_cmd_block;
	t_redirect *cur_redirect;
	char **cur_cmd;

	while (pipeline_list)
	{
		cur_cmd_block = pipeline_list->cmd_block;
		cur_redirect = cur_cmd_block->redirect;
		while (cur_redirect)
		{
			if (cur_redirect->type != 2)
			{
				cur_redirect->filename; // 얘를 확장검사, here_doc 이면 패스
			}
			cur_redirect = cur_redirect->next;
		}
		cur_cmd = cur_cmd_block->cmd;
		while (cur_cmd)
		{
			*cur_cmd++; // 얘도 확장검사
		}
		// 수정해야하는 애들은 더블포인터로 넘겨야함 -> 변수의 값이 바뀔수 있기 때문

		pipeline_list = pipeline_list->next;
	}
}

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

void print_tokens(void *content)
{
	content = (char *)content;
	ft_putendl_fd(content, 1);
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
			
			if (cur_token && ft_strchr("<>", *(char *)(cur_token->content)))
			{
				ft_printf("unexpected token \'%s\'", cur_token->content);
				return;
			}
			t_redirect *new_redirect = ft_redirect_lstnew(type, (char *)(cur_token->content));
			ft_redirect_lstadd_back(&((*cmd_block)->redirect), new_redirect);

			ft_lstdel_node(tokens, cur_token, NULL); // 문자열은 lstnew에서 써야하니 살려둬야함
			// cur_token = next_token;
			// next_token = cur_token->next;
		}
		cur_token = next_token;
	}

	// redirect operator 이후에 오는 word가 operator가 아닌지 체크
	// operator 라면 unexpected token 출력
}

void get_cmds(t_list **tokens, t_cmd_block **cmd_block)
{
	size_t cnt = 0;
	size_t idx = 0;
	t_list *cur_token;

	if (!tokens || !*tokens)
		return;
	cur_token = *tokens;
	// while (cur_token && ((*(char *)(cur_token->content)) != '|')) // 토큰이 다 떨어졌거나 파이프라면 순회 종료
	while (cur_token && ft_strcmp(cur_token->content, "|")) // 토큰이 다 떨어졌거나 파이프라면 순회 종료
	{
		cnt++;
		cur_token = cur_token->next;
	}

	if (cnt == 0)
		return;

	(*cmd_block)->cmd = (char **)calloc(cnt + 1, sizeof(char *)); // NULL 포인터가 필요한 이중배열이기때문에 +1만큼 생성

	cur_token = *tokens;
	while (idx < cnt)
	{
		(*cmd_block)->cmd[idx++] = (char *)(cur_token->content);
		ft_lstdel_node(tokens, cur_token, NULL); // 문자열이 cmd안에서 쓰여야 하니 살려둔다
		cur_token = cur_token->next;
	}
}

t_cmd_block *create_cmd_block(t_list **tokens)
{
	t_cmd_block *new_cmd_block;

	new_cmd_block = ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		return (NULL);
	get_redirections(tokens, &new_cmd_block);
	get_cmds(tokens, &new_cmd_block);
	if (new_cmd_block->redirect == NULL && new_cmd_block->cmd == NULL)
	{
		ft_printf("unexpected token: \'|\'\n");
		free(new_cmd_block);
		return (NULL);
	}
	return (new_cmd_block);
}

t_pipeline	*my_parse(char *str)
{
	t_pipeline	*pipe_list = NULL;
	t_list		*tokens = NULL;

	create_tokens(&tokens, str);
	if (!tokens)
		return (NULL); // 만드는데 실패했거나 아무것도 없는 공백이였을 경우
	while (1)
	{
		t_pipeline *new_pipeline;
		t_cmd_block *new_cmd_block;

		new_cmd_block = create_cmd_block(&tokens);
		
		if (!new_cmd_block)
			return (NULL);
		new_pipeline = ft_pipeline_lstnew(new_cmd_block);
		if (!new_pipeline)
			return (NULL);
		ft_pipeline_lstadd_back(&pipe_list, new_pipeline);

		if (tokens == NULL) // 마지막이면 종료
			break ;

		if ((*(char *)(tokens->content)) == '|') // 파이프면 파이프 지우고 계속
		{
			t_list *next_token;

			next_token = tokens->next;
			ft_lstdel_node(&tokens, tokens, free);
			tokens = next_token;
		}
	}
	return (pipe_list);
}

int main(int argc, char *argv[], char *envp[])
{
    char		*res;
	t_pipeline	*pipeline_list;
	t_data		data;

	(void)argc;
	(void)argv;
	(void)pipeline_list;
	(void)envp;

	data.my_env = init_envp(envp);
    while (1)
    {
		res = readline("yo shell$ ");

		pipeline_list = my_parse(res);
		expand_check(pipeline_list);

		// print_tree(pipeline_list);
		mini_execute(pipeline_list, &data);

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