#include "mini_parse.h"

int	get_redirection(t_token **cur_token, t_cmd_block *cmd_block)
{
	t_redirect	*new_redirect;
	int			type;

	type = 1;
	if (*(*cur_token)->value == '>')
		type = 3;
	type += (ft_strlen((*cur_token)->value) > 1);
	*cur_token = (*cur_token)->next;
	if (*cur_token == NULL || (*cur_token)->type == OPERATOR)
	{
		ft_printf("syntax error near unexpected token ");
		if (*cur_token == NULL)
			ft_printf("\'newline\'\n");
		else
			ft_printf("\'%s\'\n", (*cur_token)->value);
		return (0);
	}
	new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (new_redirect == NULL)
		exit(EXIT_FAILURE);
	new_redirect = ft_redirect_lstnew(type, (*cur_token)->value);
	ft_redirect_lstadd_back(&(cmd_block->redirect), new_redirect);
	*cur_token = (*cur_token)->next;
	return (1);
}

void	cmd_list_to_char(t_list *cmd_list, t_cmd_block *new_cmd_block)
{
	t_list	*cmd_list_iter;
	size_t	len;
	char	**cmds;

	cmd_list_iter = cmd_list;
	len = ft_lstsize(cmd_list);
	cmds = ft_calloc(len + 1, sizeof(char *));
	if (cmds == NULL)
		exit(EXIT_FAILURE);
	while (cmd_list_iter)
	{
		cmds[ft_lstsize(cmd_list) - len] = cmd_list_iter->content;
		len--;
		cmd_list_iter = cmd_list_iter->next;
	}
	ft_lstclear(&cmd_list, NULL);
	new_cmd_block->cmd = cmds;
}

void	get_cmd(t_token **cur_token, t_list **cmd_list)
{
	t_list	*new_node;
	char	*new_content;

	while (*cur_token && (*cur_token)->type == WORD)
	{
		new_content = ft_strdup((*cur_token)->value);
		if (new_content == NULL)
			exit(EXIT_FAILURE);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(cmd_list, new_node);
		*cur_token = (*cur_token)->next;
	}
}

void	free_cmd_block(t_cmd_block *cmd_block)
{
	char	**cmds;

	if (cmd_block->redirect)
		ft_redirect_lstclear(&cmd_block->redirect);
	if (cmd_block->cmd)
	{
		cmds = cmd_block->cmd;
		while (*cmds)
		{
			free(*cmds);
			cmds++;
		}
		free(cmd_block->cmd);
	}
	free(cmd_block);
}

t_cmd_block	*create_cmd_block(t_token **token_list)
{
	t_cmd_block	*new_cmd_block;
	t_list		*cmd_list;

	new_cmd_block = ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		exit(EXIT_FAILURE);
	cmd_list = NULL;
	while (*token_list && !((*token_list)->type == OPERATOR \
			&& ft_strcmp("|", (*token_list)->value) == 0))
	{
		if ((*token_list)->type == OPERATOR)
		{
			if (!get_redirection(token_list, new_cmd_block))
			{
				free(new_cmd_block);
				ft_lstclear(&cmd_list, free);
				return (NULL);
			}
		}
		else
			get_cmd(token_list, &cmd_list);
	}
	cmd_list_to_char(cmd_list, new_cmd_block);
	return (new_cmd_block);
}

void	create_pipeline_list(t_pipeline **pipe_list, t_token *token_list)
{
	t_pipeline	*new_pipeline;

	while (token_list)
	{
		new_pipeline = ft_pipeline_lstnew(&token_list);
		if (!new_pipeline)
		{
			ft_pipeline_lstclear(pipe_list);
			return ;
		}
		ft_pipeline_lstadd_back(pipe_list, new_pipeline);
		if (token_list && ft_strcmp(token_list->value, "|") == 0)
		{
			token_list = token_list->next;
			if (!token_list)
			{
				ft_printf("unexpected token: \'newline\'\n");
				ft_pipeline_lstclear(pipe_list);
				return ;
			}
		}
	}
}
