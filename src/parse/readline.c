
#include "mini_parse.h"

void print_tree(t_pipeline *pipeline_list)
{
	while (pipeline_list)
	{
		t_cmd_block	*cur_cmd_block = pipeline_list->cmd_block;
		t_redirect	*temp_redir = cur_cmd_block->redirect;
		printf("================================================\n");
		while (temp_redir)
		{
			printf("\n");
			printf("redirect type: %d\n", temp_redir->type);
			printf("redirect filename: %s\n", temp_redir->filename);
			temp_redir = temp_redir ->next;
		}
		printf("\n");
		char	**temp_cmd = cur_cmd_block->cmd;
		while (temp_cmd)
		{
			printf("current word: %s\n", *temp_cmd);
			temp_cmd++;
		}
		pipeline_list = pipeline_list ->next;
	}
}
// get number of tokens 
// white space          ' '
// redirection operator  <, >, <<, >> 
// pipe                  '|'

// operator             &&, ||

// int ft_get_number(char *res)
// {
//     int i;
//     int cnt;

//     i = 0;
//     cnt = 0;

//     while (res[i] && ft_is_space(res[i]))
//         i++;
//     while (res[i])
//     {
//         // printf("res[%d] = '%c' cnt is %d\n", i, res[i], cnt);
//         if (res[i] == '<')
//         {
//             cnt++;
//             i++;
//             if (res[i] && res[i] == '<')
//                 i++;
//         }
//         else if (res[i] == '>')
//         {
//             cnt++;
//             i++;
//             if (res[i] && res[i] == '>')
//                 i++;
//         }
//         else if (res[i] == '|')
//         {
//             cnt++;  
//             i++;
//             if (res[i] && res[i] == '|')
//                 i++;
//         }
//         else if (res[i] == '&')
//         {
//             cnt++;
//             i++;
//             if (res[i] && res[i] == '&')
//                 i++;
//         }
//         else if (res[i] == ' ')
//             i++;
//         else
//         {
//             while (res[i] && ft_is_word(res[i]))
//                 i++;
//             cnt++;
//         }
//     }
//     return (cnt);
// }

void	create_tokens(t_list **tokens, char *str)
{
	/*

		1. 문자는 공백을 기준으로 분할이됨
		2. 따옴표로 감싸있는 애들은 분할이 진행되지 않음
		3. 문자열끼리 공백없이 함쳐져있으면 하나의 문자열로 인식됨
		4. 리다이렉션 문자가 나오면 리다이렉션 문자만 따로 잘라서 인식 (파이프 포함)
		(리다이렉션이나 파이프같은 오퍼레이터는 따옴표가 없으면 따로 잘라서 인식)
		(하지만 이 오퍼레이터도 따옴표가 더 우선순위가 높음을 주의)
		5. 오퍼레이터가 공백없이 문자 도중에 나오는것도 의식할것

	*/
	
	char *token_str;
	t_list *new_node;

	while (*str)
	{
		while (*str == 32 || *str == 9 || *str == 10)
			str++;
		
		
		if (*str == '<' || *str == '>')
		{
			if ((*(str + 1) == '<' || *(str + 1) == '>'))
			{
				if (*str == *(str + 1))
				{
					token_str = ft_substr(str, 0, 2);
					str += 2;
				}
				// else
					//error
					// ft_err_msg("Syntax error with <>\n", __FILE__, __LINE__);
			}
			else
			{
				token_str = ft_substr(str, 0, 1);
				str++;
			}
			
			new_node = ft_lstnew(token_str);
			ft_lstadd_back(tokens, new_node);
		}
		else
		{
			int is_quote = 0;
			char *substr_offset = str;
			while (*str != '\0')
			{
				if (*str == '\'' || *str == '\"')
				{
					if (is_quote)
						is_quote = 0;
					else
						is_quote = 1;
				}
				else if (*str == 32 || *str == 9 || *str == 10)
				{
					if (!is_quote)
						break;
				}
				str++;
			}

			token_str = ft_substr(substr_offset, 0, str - substr_offset);

			new_node = ft_lstnew(token_str);
			ft_lstadd_back(tokens, new_node);
		}
	}
}

void print_tokens(void *content)
{
	content = (char *)content;
	ft_putendl_fd(content, 1);
}

t_cmd_block *create_cmd_block(char *str)
{
	t_cmd_block *new_cmd_block;
	t_list *tokens;

	new_cmd_block = (t_cmd_block *)ft_calloc(1, sizeof(t_cmd_block));
	if (!new_cmd_block)
		return (NULL);
	create_tokens(&tokens, str);
	ft_lstiter(tokens, print_tokens);
		
	// tokens 해석하며 cmd_block 채워넣기
	// while (tokens)
	// {
	// 	if (ft_strchr("<>", *(char *)tokens->content))
	// 		// create redirect and addback
	// 	else
	// 		// quote remove and cmd addback
	// 	tokens = tokens->next;
	// }

	return (new_cmd_block);
}

t_pipeline	*my_parse(char *str)
{
	t_pipeline	*pipe_list;
	t_list		*tokens = NULL;

	create_tokens(&tokens, str);
	ft_lstiter(tokens, print_tokens);

	(void)(pipe_list);
	// 토큰을 해석하면서 트리에 넣는 함수들
	// 단계별로 함수들이 다름
	return (0);
	// return (pipe_list);
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

int main(int argc, char *argv[], char *envp[])
{
    char    *res;
	t_pipeline *pipeline_list;

	(void)argc;
	(void)argv;
	(void)envp;

    while (1)
    {
		res = readline("yo shell$ ");

		pipeline_list = my_parse(res);
		print_tree(pipeline_list);
    }
}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : cc -lreadline read_line.c && ./a.out

// readline 의 반환값에는 따옴표도 일반적인 문자처럼 포함되어있음
// 기존 쉘에서는 따옴표를 하나의 문장으로 치환해서 해석하지만
// 여기서는 포함된채 통째로 하나의 큰 문자열로 반환해줌
// 모든것이 날것으로 남아있음