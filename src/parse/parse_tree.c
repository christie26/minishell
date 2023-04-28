
#include "mini_parse.h"

int get_redirection(t_token **cur_token, t_cmd_block *cmd_block)
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

	new_redirect = ft_redirect_lstnew(type, (*cur_token)->value);// word 뿐만 아니라 redirect 의 filename 도 문자열 주소만 옮겨주니 함부로 free 하면 안될듯
	ft_redirect_lstadd_back(&(cmd_block->redirect), new_redirect);
	*cur_token = (*cur_token)->next;
	return (1);
}

void cmd_list_to_char(t_list *cmd_list, t_cmd_block *new_cmd_block)
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

void get_cmd(t_token **cur_token, t_list **cmd_list)
{
	t_list *new_node;
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

void free_cmd_block(t_cmd_block *cmd_block)
{
	char **cmds;

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

/*

	토큰 하나씩 순회

	operator 토큰일 경우
	- 파이프일때
	- 파이프가 아닐떄
		- redirection
		- 다음토큰도 operator 면 에러 -> unexpected token 'token -> value'
		- 다음토큰이 비었으면 에러 -> unexpected token 'newline'
	word 토큰일 경우
	- 저장해뒀다가 일괄적으로 char** 로 변환...?
		- 토큰의 value를 옮겨담은 리스트를 따로 만들것인지...?
		- 토큰의 value를 strdup으로 복제한 리스트를 따로 만들것인지...?

*/
t_cmd_block *create_cmd_block(t_token **token_list)
{
	t_cmd_block *new_cmd_block;
	t_list		*cmd_list;

	new_cmd_block = ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		exit(EXIT_FAILURE);
	cmd_list = NULL;

	while (*token_list && !((*token_list)->type == OPERATOR && ft_strcmp("|", (*token_list)->value) == 0))
	{
		if ((*token_list)->type == OPERATOR)
		{
			if (!get_redirection(token_list, new_cmd_block))
			{
				free(new_cmd_block);
				return (NULL);
			}
		}
		else
			get_cmd(token_list, &cmd_list);
	}
	cmd_list_to_char(cmd_list, new_cmd_block);
	return (new_cmd_block);
}



void create_pipeline_list(t_pipeline **pipe_list, t_token *token_list)
{
	t_pipeline	*new_pipeline;

	while (token_list)
	{
		new_pipeline = ft_pipeline_lstnew(&token_list);
		if (!new_pipeline) // 파이프로 시작했거나 redirect 에러
		{
			ft_pipeline_lstclear(pipe_list);
			return ;
		}
		
		ft_pipeline_lstadd_back(pipe_list, new_pipeline);

		if (token_list && ft_strcmp(token_list->value, "|") == 0) // redirect 와 word 를 다 밀었으니 파이프나 널문자가 있을것
		{
			token_list = token_list->next;
			if (!token_list) // 파이프로 끝난경우
			{
				ft_printf("unexpected token: \'newline\'\n");
				ft_pipeline_lstclear(pipe_list);
				return ;
			}
		}
	}
}