
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
		ft_lstdel_node(tokens, prev_token, free);
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

t_cmd_block *create_cmd_block(t_list **tokens)
{
	t_cmd_block *new_cmd_block;

	new_cmd_block = ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		return (NULL);
	
	/*
		redirect, word 리스트를 각각 두고
		현재 토큰에 따라 리스트를 채워나가기?
		마지막에 word 리스트만 char **로 변환...
		확장후 오퍼레이터를 처리하기위해서는
		토큰에 타입이라는 추가정보를 달아줘야함
		그렇다면 여기서 트리를 만드는 과정도 수월해짐
	*/

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

void create_pipe_list(t_pipeline **pipe_list, t_list **tokens)
{
	t_pipeline *new_pipeline;
	t_cmd_block *new_cmd_block;
	t_list *next_token;

	while (*tokens)
	{
		new_cmd_block = create_cmd_block(tokens);
		
		if (!new_cmd_block) // 파싱 에러
		{
			ft_lstclear(tokens, free);
			ft_pipeline_lstclear(pipe_list);
			return;
		}
		
		new_pipeline = ft_pipeline_lstnew(new_cmd_block);
		if (!new_pipeline)
			exit(EXIT_FAILURE);
		
		ft_pipeline_lstadd_back(pipe_list, new_pipeline);

		if (*tokens && ft_strcmp((*tokens)->content, "|")) // 파이프면 파이프 지우고 계속
		{
			next_token = (*tokens)->next;
			ft_lstdelone(*tokens, free);
			*tokens = next_token;
		}
	}
}