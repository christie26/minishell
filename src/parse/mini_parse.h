
#ifndef MINI_PARSE_H
# define MINI_PARSE_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "../common/model.h"

t_pipeline	*ft_pipeline_lstnew(t_cmd_block *new_cmd_block);
int			ft_pipeline_lstsize(t_pipeline *pipeline_lst);
t_pipeline	*ft_pipeline_lstlast(t_pipeline *pipeline_lst);
void		ft_pipeline_lstadd_back(t_pipeline **pipeline_lst, t_pipeline *new);
void		ft_pipeline_lstclear(t_pipeline **pipeline_lst);

t_redirect	*ft_redirect_lstnew(int type, char *filename);
int	ft_redirect_lstsize(t_redirect *redirect_lst);
t_redirect	*ft_redirect_lstlast(t_redirect *redirect_lst);
void	ft_redirect_lstadd_back(t_redirect *redirect_lst, t_redirect *new);
void	ft_redirect_lstclear(t_redirect **redirect_lst);

#endif
