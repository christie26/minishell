
#include "mini_parse.h"

t_pipeline *ft_pipeline_lstnew(t_token **token_list)
{
	t_pipeline	*new_pipeline;
	t_cmd_block	*new_cmd_block;

	if ((*token_list)->type == OPERATOR && ft_strcmp("|", (*token_list)->value) == 0) // pipe로 시작하는 경우 에러, 도중에 들어왔어도 create pipelist 에서 파이프 하나 밀어주고 들어옴
	{
		ft_printf("unexpected token: \'|\'\n");
		return (NULL);
	}

	new_cmd_block = create_cmd_block(token_list);
	
	if (!new_cmd_block) // 파싱 에러 - redirect 에서 유효하지 않은 토큰이 온 경우
		return (NULL);
	
	new_pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new_pipeline)
		exit(EXIT_FAILURE);
	
	new_pipeline->cmd_block = new_cmd_block;
	new_pipeline->next = NULL;
	return (new_pipeline);
}

int	ft_pipeline_lstsize(t_pipeline *pipeline_lst)
{
	int			cnt;
	t_pipeline	*cur_pipeline;

	cnt = 0;
	cur_pipeline = pipeline_lst;
	while (cur_pipeline)
	{
		cur_pipeline = cur_pipeline->next;
		cnt++;
	}
	return (cnt);
}

t_pipeline	*ft_pipeline_lstlast(t_pipeline *pipeline_lst)
{
	t_pipeline	*cur_pipeline;

	if (!pipeline_lst)
		return (NULL);
	cur_pipeline = pipeline_lst;
	while (cur_pipeline->next)
		cur_pipeline = cur_pipeline->next;
	return (cur_pipeline);
}

void	ft_pipeline_lstadd_back(t_pipeline **pipeline_lst, t_pipeline *new)
{
	t_pipeline	*cur_pipeline;

	if (pipeline_lst == NULL)
		return;
	if (*pipeline_lst)
	{
		cur_pipeline = ft_pipeline_lstlast(*pipeline_lst);
		cur_pipeline->next = new;
	}
	else
		*pipeline_lst = new;
}

void	ft_pipeline_lstclear(t_pipeline **pipeline_lst)
{
	t_pipeline	*cur_pipeline;
	t_pipeline	*next_pipeline;

	if (*pipeline_lst)
	{
		cur_pipeline = *pipeline_lst;
		while (cur_pipeline)
		{
			next_pipeline = cur_pipeline->next;
			free_cmd_block(cur_pipeline->cmd_block);
			free(cur_pipeline);
			cur_pipeline = next_pipeline;
		}
		*pipeline_lst = 0;
	}
}
