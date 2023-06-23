/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:17:00 by yoonsele          #+#    #+#             */
/*   Updated: 2023/06/22 18:23:46 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parse.h"

int	main(int argc, char *argv[], char *envp[])
{
	char		*res;
	t_pipeline	*pipeline_list;
	t_data		data;

	if (argc != 1)
		return (error_command_msg(argv[1], START_ERROR));
	data.my_env = init_envp(envp);
	while (1)
	{
		signal_setting_readmode();
		res = readline("yo shell$ ");
		if (res == NULL)
			readline_exit();
		pipeline_list = my_parse(res, data.my_env);
		if (pipeline_list)
		{
			signal(SIGINT, SIG_IGN);
			mini_execute(pipeline_list, &data);
			free_path(data.path);
			heredoc_unlink(pipeline_list);
			ft_pipeline_lstclear(&pipeline_list);
		}
		free(res);
	}
}
