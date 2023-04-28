
#include "mini_parse.h"

void get_redirections(t_list **tokens, t_cmd_block **cmd_block)
{
	t_list *cur_token;
	t_list *prev_token;
	t_redirect *new_redirect;
	int type;

	cur_token = *tokens;
	while (cur_token && (ft_strcmp(((cur_token->content)), "|") != 0)) // 토큰이 다 떨어졌거나 파이프라면 순회 종료
	{
		if (!is_operator_char(*(char *)(cur_token->content))) // word 라면 패스
		{
			cur_token = cur_token->next;
			continue;
		}

		// ------------ 타입 구분 ------------
		type = 1; // < 을 기본값으로 먼저 세팅
		if (*(char *)(cur_token->content) == '>') // 조건부에 따라 덮어씌움
			type = 3;
		type += (*(char *)(cur_token->content) == *((char *)(cur_token->content) + 1)); // 연달아 같은 문자면 +1

		prev_token = cur_token;
		cur_token = cur_token->next;
		ft_lstdel_node(tokens, prev_token, free);

		// ----------- 에러 케이스 -----------
		if (cur_token == NULL) // redirection 으로 끝난경우
		{
			ft_printf("unexpected token \'newline\'");
			return;
		}
		else if (cur_token && is_operator_char(*(char *)(cur_token->content))) // redirection 이 연속해서 등장하는 경우
		{
			ft_printf("unexpected token \'%s\'", cur_token->content);
			return;
		}
		// -----------------------------------

		// ------------ 파일 이름 ------------
		new_redirect = ft_redirect_lstnew(type, (char *)(cur_token->content));
		ft_redirect_lstadd_back(&((*cmd_block)->redirect), new_redirect);

		prev_token = cur_token;
		cur_token = cur_token->next;
		ft_lstdel_node(tokens, prev_token, NULL);
	}
	
	/*
		굳이 여기서 순회하며 찾아야하나 싶음
		cmd에서 편하게 일괄처리하고싶었다지만...
		그냥 밖에서 redirect, word 따라 함수를 개별로 호출하는편이...
	*/
}

void get_cmds(t_list **tokens, t_cmd_block **cmd_block)
{
	size_t cnt = 0;
	size_t idx = 0;
	t_list *cur_token;
	t_list *next_token;

	cur_token = *tokens;
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
		next_token = cur_token->next;
		(*cmd_block)->cmd[idx++] = (char *)(cur_token->content);
		ft_lstdel_node(tokens, cur_token, NULL); // 문자열이 cmd안에서 쓰여야 하니 살려둔다
		cur_token = next_token;
	}
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
t_cmd_block *create_cmd_block(t_token *token_list) // 토큰으로 트리를 만들고나면 항상 다음 토큰이 헤더이길 바래서 이중포인터로 보냈었음...
{
	t_cmd_block *new_cmd_block;

	new_cmd_block = ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		exit(EXIT_FAILURE);

	while (token_list)
	{
		if (token_list->type == OPERATOR)
		{
			if (ft_strcmp("|", token_list->value) == 0)
				break ;
			get_redirection();
		}
		else
			get_cmd();
		token_list = token_list->next;
	}
	if (new_cmd_block->redirect == NULL && new_cmd_block->cmd == NULL)
	{
		ft_printf("unexpected token: \'|\'\n");
		free(new_cmd_block);
		return (NULL);
	}
	return (new_cmd_block);

	// -----
	get_redirections(&token_list, &new_cmd_block); // 여기서 이중포인터로 보내버리기? -> 다음 토큰부터 체크할수있음, redirection
	get_cmds(&token_list, &new_cmd_block);
	if (new_cmd_block->redirect == NULL && new_cmd_block->cmd == NULL)
	{
		ft_printf("unexpected token: \'|\'\n");
		free(new_cmd_block);
		return (NULL);
	}
	return (new_cmd_block);
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

	이전까진 토큰을 순회하며 확인한 토큰을 하나씩 지우면서 진행했지만...
	그냥 여기서는 순회하면서 읽기만하고 마지막에 밖에서 한번에 날려버리면...?
	헤더를 기준으로 clear를 해버리니까 더 편하지 않을까?
	모르겠다...

*/
void create_pipe_list(t_pipeline **pipe_list, t_token **token_list)
{
	t_pipeline	*new_pipeline;
	t_cmd_block	*new_cmd_block;
	t_token		*next_token;

	while (*token_list)
	{
		new_cmd_block = create_cmd_block(token_list);
		
		if (!new_cmd_block) // 파싱 에러
		{
			ft_token_lstclear(token_list);
			ft_pipeline_lstclear(pipe_list);
			return;
		}
		
		new_pipeline = ft_pipeline_lstnew(new_cmd_block);
		if (!new_pipeline)
			exit(EXIT_FAILURE);
		
		ft_pipeline_lstadd_back(pipe_list, new_pipeline);

		if (*token_list && ft_strcmp((*token_list)->value, "|") == 0) // 파이프면 파이프 지우고 계속
		{
			next_token = (*token_list)->next;
			ft_lstdelone(*token_list, free);
			*token_list = next_token;
		}

		if (*token_list)
	}
}