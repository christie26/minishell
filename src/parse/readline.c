
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

t_cmd_block *create_cmd_block(char *str)
{
	t_cmd_block *new_cmd_block;

	new_cmd_block = (t_cmd_block *)ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		return (NULL);
	new_cmd_block->redir; // redirect부터 처리
	new_cmd_block->cmd; // redirect가 제거된 문자열을 cmd에 split으로 대입
	return (new_cmd_block);
}

t_list	*create_pipe(char *str)
{
	t_list		*new_pipe;
	t_cmd_block *new_cmd_block;

	new_cmd_block = create_cmd_block(str);
	if (!new_cmd_block)
		return (NULL);
	new_pipe = ft_lstnew(new_cmd_block);
	if (!new_pipe)
	{
		free(new_cmd_block);
		return (NULL);
	}
	return (new_pipe);
}

t_list	*my_parse(char *str)
{
	// split
	// 순회하며 pipe 구조체 작성 (t_list)
	// - cmd block 생성
	// - redirection 처리 (t_list)
	// - command char**로 처리

	char	**pipe_lines;
	t_list	*pipe_list;
	t_list	*new_pipe;

	pipe_lines = ft_split(str, '|');
	pipe_list = NULL;
	while (pipe_lines)
	{
		new_pipe = create_pipe(pipe_lines);
		ft_lstadd_back(&pipe_list, new_pipe);
		pipe_lines++;
	}
	return (pipe_list);
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
/*
	spilt을 사용해서 pipe단위로 문자열을 긁어냄
	그 char **문자열이 null이 될때까지 순회하며 list 구조체 생성
	pipe 단위에서도 구조체가 그냥 list쓰면 될것같음
	void* content에 cmd_block만 넣기
*/

int main(void)
{
    char    *res;
	char	**split_by_pipe;
	char	**temp2;

    while (1)
    {
		res = readline("yo shell$ ");
		// printf("cmd read: %s\nget token number: %d\n", res, ft_get_number(res));
		ft_printf("input: %s\npipe cnt: %d\n", res, get_pipe_cnt(res));
		split_by_pipe = ft_split(res, '|');
		ft_printf("split strings: ");
		temp2 = split_by_pipe;
		while (*temp2)
			ft_printf("\"%s\" ", *temp2++);
		ft_printf("\n");
		free(res);
    }
    

}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : cc -lreadline read_line.c && ./a.out 