#ifndef BUILT_IN_H

# define BUILT_IN_H

# include <stdio.h>

# include "../../libft/includes/libft.h"
# include "../model.h"
# include "../error.h"

// built-in files
int     ft_echo(char *cmd, char **options, char **env);
int     ft_cd(char *cmd, char **options, char **env);
int     ft_pwd(char *cmd, char **options, char **env);
int     ft_export(char *cmd, char **options, char **env);
int     ft_unset(char *cmd, char **options, char **env);
int     ft_env(char *cmd, char **options, char **env);
int     ft_exit(char *cmd, char **options, char **env);

char	*get_value(char *key, char **env);

#endif