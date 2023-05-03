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
	new_redirect = ft_redirect_lstnew(type, (*cur_token)->value);
	ft_redirect_lstadd_back(&(cmd_block->redirect), new_redirect);
	*cur_token = (*cur_token)->next;
	return (1);
}
