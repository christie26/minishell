#include "mini_parse.h"

/*

	시그널 핸들링
	1. 입력모드일때
	- 내용 상관없이 sigint는 버퍼를 비우고 프롬프트를 다시 표시함
	- 내용 상관없이 sigquit는 무반응?
	- 내용이 없으면 eof은 exit, 내용이 있으면 eof은 무반응
	
	2. 실행모드일때
	- sigint, sigquit, eof 기본값?

	eof : 터미널 구조체를 사용해서 처리하는듯

	-Read a string, and return a pointer to it.
	Returns NULL on EOF.
	
	readline 의 반환값을 보면 eof 경우엔 NULL을 반환한다고 한다
	터미널 설정을 안하고 그냥 readline의 반환값으로 체크하면 되는걸까...

	exit state + signum
	sigint -> 130
	sigquit -> 131

	sigint sigquit는 실행모드일때 기본동작으로 설정하면
	쉘이 종료되버린다...
	종료되지 않고 다시 프롬프트로 돌아오려면?

*/

void	sig_handler_readmode(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line(); // 줄이 바뀌었다고 알림
		// rl_replace_line("", 1); // 바뀐 줄의 내용을 비운다고 알림
		rl_redisplay(); // 바뀐 줄을 표시 함
		ft_printf("hi\n");
	}
}

void	signal_setting_readmode(void)
{
	if (signal(SIGINT, sig_handler_readmode) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	signal_setting_commandmode(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	signal_setting_heredocmode(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}
