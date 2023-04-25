
#include "mini_parse.h"

/*

	시그널 핸들링
	1. 입력모드일때
	- 내용 상관없이 sigint는 버퍼를 비우고 프롬프트를 다시 표시함
	- 내용이 없으면 eof은 exit, 내용이 있으면 eof은 무반응
	- 내용 상관없이 sigkil은 무반응?
	
	2. 실행모드일때
	- sigint, sigkill, eof 기본값?

*/