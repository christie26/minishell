
#include "mini_parse.h"

int	short_exit_status;

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

t_pipeline	*my_parse(char *str, char **my_env)
{
	t_pipeline	*pipe_list = NULL;
	t_list		*tokens = NULL;

	create_tokens(&tokens, str);
	if (!tokens)
		return (NULL); // 만드는데 실패했거나 아무것도 없는 공백이였을 경우

	t_list		*tokens_iter = tokens;
	while (tokens_iter)
	{
		char *content = get_expanded_string(tokens_iter->content, my_env);;
		if (tokens_iter == NULL)
		{
			ft_lstclear(&tokens, free);
			ft_pipeline_lstclear(&pipe_list);
			return (NULL);
		}
		free(tokens_iter->content);
		tokens_iter->content = content;
		tokens_iter = tokens_iter->next;
	}

	ft_lstiter(tokens, print_tokens);

	quote_remove_check(tokens);
	(void)my_env;

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
	set_exit_status(&data, 0);
    while (1)
    {
		res = readline("yo shell$ ");

		pipeline_list = my_parse(res, data.my_env);
		if (pipeline_list)
		{
			add_history(res); // 나중에 유효성검사후 추가 삭제 제어를 검토할것

			// print_tree(pipeline_list);

			// mini_execute(pipeline_list, &data);
		}
		free(res);
		// while (*res)
			// ft_printf("c: %d\n", *res++);
		// ft_printf("res p: %p\n", res);
    }
}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : cc -lreadline read_line.c && ./a.out
