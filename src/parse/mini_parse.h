#ifndef MINI_PARSE_H
# define MINI_PARSE_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <signal.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "../model.h"
# include "../built_in/mini_builtin.h"

enum e_token_type
{
	OPERATOR,
	WORD
};

typedef struct s_token {
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

// readline.c
void		print_tree(t_pipeline *pipeline_list);
t_pipeline	*my_parse(char *str, char **my_env);

// parse_simple_check.c
int			is_blank(char c);
int			is_operator_char(char c);
int			is_metacharacter(char c);
int			is_quote(char c);

// new_parse_token.c
char		*get_operator(char *str, size_t *idx);
char		*get_word_with_quote(char *str, size_t *idx);
void		create_tokens(t_token **token_list, char *input);

// new_parse_tree.c
int			get_redirection(t_token **cur_token, t_cmd_block *cmd_block);
void		cmd_list_to_char(t_list *cmd_list, t_cmd_block *new_cmd_block);
void		get_cmd(t_token **cur_token, t_list **cmd_list);
void		free_cmd_block(t_cmd_block *cmd_block);
t_cmd_block	*create_cmd_block(t_token **token_list);
void		create_pipeline_list(t_pipeline **pipe_list, t_token *token_list);

// parse_expand.c
int			is_expandable(char *word);
void		expand_check(t_list *tokens, char **my_env);
void		quote_remove_check(t_list *tokens);
void		quote_removal(t_list *token);

void		expand_tokens(t_token **token_list, char **my_env);
char		*word_list_join(t_list *word_list);
char		*get_key_from_word(char **str);
char		*get_expanded_word(char **str, char **my_env);
char		*get_non_expanded_word(char **str);
char		*get_expanded_string(char *str, char **my_env);

// parse_quote_remove.c
char		*get_word_with_operator(char **word);
void		word_splitting(t_token **new_list, char *word);
void		splitting_tokens(t_token **token_list);
void		quote_remove_tokens(t_token **token_list);
char		*get_word_without_quote(char *str, size_t *idx);
char		*get_quote_removed_string(char *str);

// signals.c
void		sig_handler_readmode(int signum);
void		signal_setting_readmode(void);
void		signal_setting_commandmode(void);

// pipeline_list_utils.c
t_pipeline	*ft_pipeline_lstnew(t_token **token_list);
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

// token_list_utils.c
t_token		*ft_token_lstnew(int type, char *value);
t_token		*ft_token_lstlast(t_token *token_lst);
void		ft_token_lstadd_back(t_token **token_lst, t_token *new);
void		ft_token_lstdel_node(t_token **token_lst, t_token *target);
void		ft_token_lstclear(t_token **token_lst);

// with execute
int			mini_execute(t_pipeline *pipeline, t_data *data);
char		**init_envp(char **envp);
void		set_exit_status(t_data *data, int g_exit_status);

#endif
