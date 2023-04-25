
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
# include "../model.h"
# include "../built_in/built_in.h"

// readline.c
void print_tree(t_pipeline *pipeline_list);
t_pipeline	*my_parse(char *str, char **my_env);

// parse_utils1.c
int is_blank(char c);
int is_operator_char(char c);
int is_metacharacter(char c);
int is_quote(char c);

// parse_utils2.c
void print_tokens(void *content);
char *get_operator(char **input);
char *get_word_with_quote(char **input);
void	create_tokens(t_list **tokens, char *str);

// parse_utils3.c
void get_redirections(t_list **tokens, t_cmd_block **cmd_block);
void get_cmds(t_list **tokens, t_cmd_block **cmd_block);
t_cmd_block *create_cmd_block(t_list **tokens);
void free_cmd_block(t_cmd_block *cmd_block);

// parse_utils4.c
int	is_expandable(char *word);
void expand_check(t_list *tokens, char **my_env);
void quote_remove_check(t_list *tokens);
void quote_removal(t_list *token);

// pipeline_list_utils.c
t_pipeline	*ft_pipeline_lstnew(t_cmd_block *new_cmd_block);
int			ft_pipeline_lstsize(t_pipeline *pipeline_lst);
t_pipeline	*ft_pipeline_lstlast(t_pipeline *pipeline_lst);
void		ft_pipeline_lstadd_back(t_pipeline **pipeline_lst, t_pipeline *new);
void		ft_pipeline_lstclear(t_pipeline **pipeline_lst);

// redirect_list_utils.c
t_redirect	*ft_redirect_lstnew(int type, char *filename);
int			ft_redirect_lstsize(t_redirect *redirect_lst);
t_redirect	*ft_redirect_lstlast(t_redirect *redirect_lst);
void		ft_redirect_lstadd_back(t_redirect **redirect_lst, t_redirect *new);
void		ft_redirect_lstclear(t_redirect **redirect_lst);

// with execute
int         mini_execute(t_pipeline *pipeline, t_data *data);
char		**init_envp(char **envp);

#endif
