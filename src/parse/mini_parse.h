
#ifndef MINI_PARSE_H
# define MINI_PARSE_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"

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

typedef struct s_cmd_block {
	t_redirect	*redirect;
	char		**cmd;
}   t_cmd_block;

typedef struct s_prc_block {
    t_cmd_block			*cmd_block;
    struct s_prc_block	*next_prc;
} t_prc_block;

int ft_is_space(char c);
int ft_is_word(char c);

#endif
