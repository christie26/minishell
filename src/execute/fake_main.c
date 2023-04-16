#include "./mini_exec.h"

int main(int ac, char **av, char **env)
{
	t_pipeline	pipe_1, pipe_2, pipe_3;
	t_cmd_block	cmd_1, cmd_2, cmd_3;
	t_redirect	red_2, red_3;

	pipe_1.next = 0;
	pipe_2.next = 0; 
	// pipe_2.next = &pipe_3;
	// pipe_3.next = 0;
//
	pipe_1.cmd_block = &cmd_1;
	pipe_2.cmd_block = &cmd_2;
	pipe_3.cmd_block = &cmd_3;
//
	cmd_1.cmd = ft_split("cd happy", ' ');
	cmd_2.cmd = ft_split("cat", ' ');
	cmd_3.cmd = ft_split("cat", ' ');
//
	cmd_1.redirect = 0;
	cmd_2.redirect = 0;
	cmd_3.redirect = 0;
//
	red_2.type = 1;
	red_2.filename = "happy";
	red_2.next = &red_3;
//
	red_3.type = 3;
	red_3.filename = "sad";
	red_3.next = 0;
	// // cmd_3.redirect = 0;
	// // (void)(red_3);
	// cmd_3.redirect = &red_3;
	// red_3.type = 3;
	// red_3.filename = "result";
	// red_3.next = 0;

	(void)(ac);
	(void)(av);
	mini_execute(&pipe_1, env);
	return (0);
}

// cat a | cat < happy | cat > result

