#include "mini_parse.h"

void	print_tree2(t_redirect *temp_redir)
{
	while (temp_redir)
	{
		ft_printf("\n");
		ft_printf("redirect type: %d\n", temp_redir->type);
		ft_printf("redirect filename: %s\n", temp_redir->filename);
		temp_redir = temp_redir->next;
	}
}

void	print_tree(t_pipeline *pipeline_list)
{
	size_t		idx;
	t_cmd_block	*cur_cmd_block;
	t_redirect	*temp_redir;
	char		**temp_cmd;

	idx = 0;
	while (pipeline_list)
	{
		ft_printf("================= pipeline %d ==================\n\n", idx++);
		cur_cmd_block = pipeline_list->cmd_block;
		ft_printf("--- redirect ---\n");
		temp_redir = cur_cmd_block->redirect;
		print_tree2(temp_redir);
		ft_printf("\n");
		ft_printf("--- cmd ---\n\n");
		temp_cmd = cur_cmd_block->cmd;
		while (temp_cmd && *temp_cmd)
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
	if (!tokens)
		return (NULL);
	add_history(str);
	expand_tokens(&tokens, my_env);
	if (!tokens)
		return (NULL);
	splitting_tokens(&tokens);
	quote_remove_tokens(&tokens);
	if (!tokens)
		return (NULL);
	create_pipeline_list(&pipe_list, tokens);
	ft_token_lstclear(&tokens);
	return (pipe_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*res;
	t_pipeline	*pipeline_list;
	t_data		data;

	if (argc != 1)
	{
		error_command_msg(argv[1], START_ERROR);
		return (1);
	}
	data.my_env = init_envp(envp);
	set_exit_status(&data, 0);
	while (1)
	{
		signal_setting_readmode();
		res = readline("yo shell$ ");
		if (res == NULL)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		pipeline_list = my_parse(res, data.my_env);
		if (pipeline_list)
		{
			if (signal(SIGINT, SIG_IGN) == SIG_ERR)
				exit(EXIT_FAILURE);
			mini_execute(pipeline_list, &data);
			ft_pipeline_lstclear(&pipeline_list);
		}
		free(res);
	}
}
