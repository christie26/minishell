
#include "mini_parse.h"

t_redirect	*ft_redirect_lstnew(int type, char *filename)
{
	t_redirect	*new_redirect_lst;

	new_redirect_lst = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new_redirect_lst)
		return (0);
	new_redirect_lst->type = type;
	new_redirect_lst->filename = filename;
	new_redirect_lst->next = NULL;
	return (new_redirect_lst);
}


int	ft_redirect_lstsize(t_redirect *redirect_lst)
{
	int			cnt;
	t_redirect	*cur_redirect;

	cnt = 0;
	cur_redirect = redirect_lst;
	while (cur_redirect)
	{
		cur_redirect = cur_redirect->next;
		cnt++;
	}
	return (cnt);
}

t_redirect	*ft_redirect_lstlast(t_redirect *redirect_lst)
{
	t_redirect	*cur_redirect;

	if (!redirect_lst)
		return (NULL);
	cur_redirect = redirect_lst;
	while (cur_redirect->next)
		cur_redirect = cur_redirect->next;
	return (cur_redirect);
}

void	ft_redirect_lstadd_back(t_redirect *redirect_lst, t_redirect *new)
{
	t_redirect	*cur_redirect;

	if (redirect_lst == NULL)
		return;
	if (*redirect_lst)
	{
		cur_redirect = ft_redirect_lstlast(*redirect_lst);
		cur_redirect->next = new;
	}
	else
		*redirect_lst = new;
}

void	ft_redirect_lstclear(t_redirect **redirect_lst)
{
	t_redirect	*cur_redirect;
	t_redirect	*next_redirect;

	if (*redirect_lst)
	{
		cur_redirect = *redirect_lst;
		while (cur_redirect)
		{
			next_redirect = cur_redirect->next;
			free(cur_redirect->filename);
			free(cur_redirect);
			cur_redirect = next_redirect;
		}
		*redirect_lst = 0;
	}
}
