/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:33:00 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 20:33:01 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parse.h"

void	sig_handler_readmode(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	signal_setting_readmode(void)
{
	struct termios	my_terminal;

	tcgetattr(STDIN_FILENO, &my_terminal);
	my_terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &my_terminal);
	signal(SIGINT, sig_handler_readmode);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_setting_commandmode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_setting_heredocmode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
