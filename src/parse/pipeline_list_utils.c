
#include "mini_parse.h"

t_pipeline	*ft_pipeline_lstnew(t_cmd_block *new_cmd_block)
{
	t_pipeline	*new_pipeline_lst;

	new_pipeline_lst = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new_pipeline_lst)
		return (0);
	new_pipeline_lst->cmd_block = new_cmd_block;
	return (new_pipeline_lst);
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

void	ft_pipeline_lstadd_back(t_pipeline *pipeline_lst, t_pipeline *new)
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
			next_pipeline = current->next;
			cur_pipeline->cmd_block;// cmd_block free 함수
			free(cur_pipeline);
			cur_pipeline = next_pipeline;
		}
		*pipeline_lst = 0;
	}
}
