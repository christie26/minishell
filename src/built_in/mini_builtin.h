#ifndef MINI_BUILTIN_H

# define MINI_BUILTIN_H

# include <stdio.h>

# include "../../libft/includes/libft.h"
# include "../model.h"
# include "../error.h"

int		ft_builtin(char **argv, t_data *data);
int		is_builtin(char *cmd);
char	**init_envp(char **envp);

// built-in files
int		ft_echo(char **options, char **env);
int		ft_cd(t_data *data, char **options, char **env);
int		ft_pwd(char *cmd, char **options, char **env);
int		ft_export(char **options, t_data *data);
int		ft_unset(char **options, t_data *data);
int		ft_env(char *cmd, char **options, char **env);
int		ft_exit(char *cmd, char **options, char **env);

// utils
char	*get_value(char *key, char **env);
int		key_exist(char *key, t_data *data, int len);
char	**get_env(char **env);
void	print_variable(char *str);
void	add_variable(char *key_value, t_data *data);

#endif