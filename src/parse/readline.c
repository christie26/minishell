
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