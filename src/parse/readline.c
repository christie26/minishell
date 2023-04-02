
#include "mini_parse.h"

// get number of tokens 
// white space          ' '
// redirection operator <, >, <<, >> 
// pipe                 '|'
// operator             &&, ||

int ft_get_number(char *res)
{
    int i;
    int cnt;

    i = 0;
    cnt = 0;

    while (res[i] && ft_is_space(res[i]))
        i++;
    while (res[i])
    {
        // printf("res[%d] = '%c' cnt is %d\n", i, res[i], cnt);
        if (res[i] == '<')
        {
            cnt++;
            i++;
            if (res[i] && res[i] == '<')
                i++;
        }
        else if (res[i] == '>')
        {
            cnt++;
            i++;
            if (res[i] && res[i] == '>')
                i++;
        }
        else if (res[i] == '|')
        {
            cnt++;  
            i++;
            if (res[i] && res[i] == '|')
                i++;
        }
        else if (res[i] == '&')
        {
            cnt++;
            i++;
            if (res[i] && res[i] == '&')
                i++;
        }
        else if (res[i] == ' ')
            i++;
        else
        {
            while (res[i] && ft_is_word(res[i]))
                i++;
            cnt++;
        }
    }
    return (cnt);
}

int	get_pipe_cnt(char *str)
{
	int cnt;

	cnt = 0;
	while (ft_strchr(str, '|'))
	{
		str = ft_strchr(str, '|');
		if (*(str + 1) != '|')
			cnt++;
		while (*str == '|' && *str != '\0')
			str++;
		ft_printf("cur str: %s\n", str);
	}
	return (cnt);
}
/*
	파이프 구분이 잘 되었다면
	파이프를 기준으로 앞뒤 문자열을 잘라서
	해당 문자열을 기준으로 하나의 pipe 구조체를 작성
	|| |||| 와 같이 여러 파이프가 연속해서 들어오거나
	" ' 같이 하나의 따옴표만 들어올 경우는 잠시 보류

	해당 문자열에서 리다이렉션이 발견되면 리다이렉션 lst_addback
	그럼 이전에 만든 t_redirection은...? -> 내용부분만 잘라내서 void* content에 넣기
	기존의 lst 타입 활용하면 libft함수를 사용할수있음
	
	리다이렉션 이외의 문자열은 split을 사용해서 char **로 저장
	리다이렉션들부터 먼저 처리!

	리다이렉션은 (방향) (파일이름) 과 같은 단순한 형태만 우선 고려하기로...
*/

int main(void)
{
    char    *res;

    while (1)
    {
		res = readline("yo shell$ ");
		// printf("cmd read: %s\nget token number: %d\n", res, ft_get_number(res));
		ft_printf("input: %s\npipe cnt: %d\n", res, get_pipe_cnt(res));
		free(res);
    }
    

}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : cc -lreadline read_line.c && ./a.out 