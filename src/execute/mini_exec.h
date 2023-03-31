
#ifndef MINI_EXEC_H

# define MINI_EXEC_H

# define READ 0
# define WRITE 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "../../libft/src/libft.h"


typedef struct s_process {
    int     order; 
    int     read_fd;        // 0 -> STDIO | 1 -> pipe | 2 -> file | 3 -> here_doc
    char    *read_file;     // if read == 0 or 1, it's NULL
    int     write_fd;       // 0 -> STDIO | 1 -> pipe | 2 -> redirect | 3 -> append
    char    *write_file;    // if read == 0 or 1, it's NULL
    int     pipe;           
    char    *cmd;
    char    **options;
}   t_process;

typedef struct s_data {
    int         number;
    pid_t       *pid_set;
    t_process   *process;

}   t_data;


int     execute_center(t_data *data, char **env);

void	duplicate_fd(int read_end, int write_end, char *file, int line);
void	close_fd(int fd, char *file, int line);

void	ft_err_msg(int condition, char *error_message, char *file, int line);
void	ft_err_sys(int condition, char *file, int line);

int     ft_echo(char *cmd, char **options, char **env);
int     ft_cd(char *cmd, char **options, char **env);
int     ft_pwd(char *cmd, char **options, char **env);
int     ft_export(char *cmd, char **options, char **env);
int     ft_unset(char *cmd, char **options, char **env);
int     ft_env(char *cmd, char **options, char **env);
int     ft_exit(char *cmd, char **options, char **env);


#endif
