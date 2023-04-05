
#include "mini_parse.h"

// get number of tokens 
// white space          ' '
// redirection operator  <, >, <<, >> 
// pipe                  '|'

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

int main(void)
{
    char    *res;

    while (1)
    {
    res = readline("minishell >> ");
    printf("cmd read: %s\nget token number: %d\n", res, ft_get_number(res));

    }
    

}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : 
// cc -lreadline readline.c parse_utils.c && ./a.out 