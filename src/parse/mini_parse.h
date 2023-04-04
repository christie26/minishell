
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

// typedef struct s_command {
// 	char    **cmd;
// }   t_command;

typedef struct s_redirect {
    int					type;           // 아래에 있음 
    char				*filename;      
    struct s_redirect	*next;
}   t_redirect;
/*
type
1: < 
2: << 
3: > 
4: >>
*/ 

// typedef struct s_redir_info {
//     int		type;			// 아래에 있음 
//     char	*filename;
// }	t_redir_info;
/*
type
1: < 
2: << 
3: > 
4: >>
*/ 

// typedef struct s_cmd_block {
// 	t_list	*redir;
// 	char	**cmd;
// }   t_cmd_block;

typedef struct s_cmd_block {
	t_redirect	*redir;
	char		**cmd;
}   t_cmd_block;

typedef struct s_pipeline {
    t_cmd_block			*cmd_block;
    struct s_pipeline	*next_pipe;
}	t_pipeline;

int ft_is_space(char c);
int ft_is_word(char c);

t_pipeline	*ft_pipeline_lstnew(t_cmd_block *new_cmd_block);
int			ft_pipeline_lstsize(t_pipeline *pipeline_lst);
t_pipeline	*ft_pipeline_lstlast(t_pipeline *pipeline_lst);
void		ft_pipeline_lstadd_back(t_pipeline *pipeline_lst, t_pipeline *new);
void		ft_pipeline_lstclear(t_pipeline **pipeline_lst);



#endif

/*

	char *origin = "<a < a < a cat > a >> a < a";

	after process
	origin = "< a < a < a cat > a >> word1 word2 a < a";

	t_redirect : "<, <, <, >, >>"
	char **cmd : "cat" "word1" "word2" NULL -> double pointer 

*/