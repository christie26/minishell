#ifndef MODEL_H

# define MODEL_H

# include <unistd.h>

int	g_exit_status;

typedef struct s_redirect {
	int					type;
	char				*filename;	
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd_block {
	t_redirect	*redirect;
	char		**cmd;
}	t_cmd_block;

typedef struct s_pipeline {
	t_cmd_block			*cmd_block;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_data {
	int		process_number;
	pid_t	*pid_set;
	int		prev_fd;
	char	**path;
	char	**my_env;
}	t_data;

int		error_command_msg(char *cmd, char *message);
int		error_command(char *cmd);

void	sig_handler_readmode(int signum);
void	signal_setting_readmode(void);
void	signal_setting_commandmode(void);

#endif