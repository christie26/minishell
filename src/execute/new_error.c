#include "./mini_exec.h"

void	error_command_msg(char *cmd, char *message)
{
	char	*cmd_extra;
	char	*shell;
	char	*with_message;

	cmd_extra = ft_strjoin(cmd, ": ");
	if (!cmd_extra)
		exit(EXIT_FAILURE);
	shell = ft_strjoin("yo shell: ", cmd_extra);
	if (!shell)
		exit(EXIT_FAILURE);
	free(cmd_extra);
	with_message = ft_strjoin(shell, message);
	if (!with_message)
		exit(EXIT_FAILURE);
	write(2, with_message, ft_strlen(with_message));
}

void	error_command(char *cmd)
{
	char	*cmd_extra;
	char	*shell;

	cmd_extra = ft_strjoin(cmd, ": ");
	if (!cmd_extra)
		exit(EXIT_FAILURE);	
	shell = ft_strjoin("yo shell: ", cmd_extra);
	if (!shell)
		exit(EXIT_FAILURE);
	free(cmd_extra);
	perror(shell);
}
