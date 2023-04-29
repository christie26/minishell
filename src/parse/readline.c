
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
	t_pipeline	*pipe_list;
	t_token		*tokens;

	(void)my_env;

	pipe_list = NULL;
	tokens = NULL;
	create_tokens(&tokens, str);
	// if (!tokens) // 만드는데 실패했거나 아무것도 없는 공백이였을 경우
	// 	return (NULL);
	add_history(str); // 공백뺴고는 전부 들어가야함

	expand_tokens(&tokens, my_env);
	if (!tokens) // bad substitution or not closed brace
		return (NULL);
	
	splitting_tokens(tokens); // 공백만 있는 토큰인경우...
	
	quote_remove_tokens(&tokens);
	if (!tokens) // 따옴표가 닫히지 않은 경우
		return (NULL);

	create_pipeline_list(&pipe_list, tokens);
	ft_token_lstclear(&tokens);

	return (pipe_list);
}

int main(int argc, char *argv[], char *envp[])
{
    char		*res;
	t_pipeline	*pipeline_list;
	t_data		data;

	(void)argc;
	(void)argv;

	data.my_env = init_envp(envp);
	set_exit_status(&data, 0);
    while (1)
    {
		res = readline("yo shell$ ");
		pipeline_list = my_parse(res, data.my_env);
		if (pipeline_list)
		{
			
			mini_execute(pipeline_list, &data);
			ft_pipeline_lstclear(&pipeline_list);
		}
		// system("leaks minishell");
		free(res);
    }
}
