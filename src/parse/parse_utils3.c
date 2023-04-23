
#include "mini_parse.h"

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
	t_list *next_token;

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
