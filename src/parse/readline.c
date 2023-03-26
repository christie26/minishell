#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char    *res;

    res = readline("minishell >> ");
    printf("%s\n", res);

}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : cc -lreadline read_line.c && ./a.out 