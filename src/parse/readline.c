
#include "mini_parse.h"

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

		따옴표는 다음따옴표가 나올때까지 인덱스를 밀고 substr 사용
		redirection 문자가 나오면 바로 flag 설정하고 redirection 만들기
		꺽쇄를 strchr로 찾아서 인덱스를 타입숫자로 넣기
		뒤에 공백이 오면 다음 문자를 filename에, 공백이 없으면 다음문자가 나올때까지
		탐색후 문자를 filename에 넣기, 후자의 조건을 while문으로 먼저 검사하면 될듯

		근데 여기선 토큰화를 하는거니까 그냥 공백단위로 다 쪼개기
		따옴표만 위에서 말한대로 특수처리

	*/
	
	char *token_str;
	t_list *new_node;

	while (*str)
	{
		while (*str == 32 || *str == 9 || *str == 10)
			str++;
		
		if (*str == '<' || *str == '>')
		{
			if ((*(str + 1) == '<' || *(str + 1) == '>') && *str == *(str + 1))
			{
				token_str = ft_substr(str, 0, 2);
				str += 2;
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
	// (void)new_cmd_block->redirect; // redirect 저장
	// 변수설정 저장
	// (void)new_cmd_block->cmd; // expaned 된 문자열을 list에 substr로 넣어놧다가 char**로 옮겨담기 (expanded 가 된 후 공백이 있으면 별개의 word로 구별하는듯함)


	return (new_cmd_block);
}

t_pipeline	*my_parse(char *str)
{
	// split
	// 순회하며 pipe 구조체 작성 (t_list)
	// - cmd block 생성
	// - redirection 처리 (t_list)
	// - command char**로 처리

	char	**pipe_lines;
	t_pipeline	*pipe_list;
	t_pipeline	*new_pipeline;
	t_cmd_block *new_cmd_block;

	pipe_lines = ft_split(str, '|');
	pipe_list = NULL;
	while (pipe_lines)
	{
		new_cmd_block = create_cmd_block(*pipe_lines);
		new_pipeline = ft_pipeline_lstnew(new_cmd_block);
		if (!new_pipeline || !new_pipeline->cmd_block) // 노드생성 실패 || 컨텐츠 생성 실패
		{
			// new_cmd_block;// cmd_block free 함수
			ft_pipeline_lstclear(&pipe_list);
			return (NULL);
		}
		ft_pipeline_lstadd_back(&pipe_list, new_pipeline);
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

int main(int argc, char *argv[], char *envp[])
{
    char    *res;
	// char	**split_by_pipe;
	// char	**temp2;

	(void)argc;
	(void)argv;
	(void)envp;
    while (1)
    {
		res = readline("yo shell$ ");
		// printf("cmd read: %s\nget token number: %d\n", res, ft_get_number(res));
		// ft_printf("input: %s\npipe cnt: %d\n", res, get_pipe_cnt(res));
		// split_by_pipe = ft_split(res, '|');
		// ft_printf("split strings: ");
		// temp2 = split_by_pipe;
		// while (*temp2)
		// 	ft_printf("\"%s\" ", *temp2++);
		// ft_printf("\n");

		t_list *tokens;
		create_tokens(&tokens, res);
		ft_lstiter(tokens, print_tokens);

		// t_pipeline *my_pipelist = my_parse(res);
		// t_pipeline *temp = my_pipelist;
		// while (temp)
		// {
		// 	t_cmd_block	*cur_cmd_block = temp->cmd_block;
		// 	t_redirect	*temp_redir = cur_cmd_block->redirect;
		// 	printf("================================================\n");
		// 	while (temp_redir)
		// 	{
		// 		printf("\n");
		// 		printf("redir type: %d\n", temp_redir->type);
		// 		printf("redir filename: %s\n", temp_redir->filename);
		// 		temp_redir = temp_redir ->next;
		// 	}
		// 	printf("\n");
		// 	char	**temp_cmd = cur_cmd_block->cmd;
		// 	while (temp_cmd)
		// 	{
		// 		printf("cur word: %s\n", *temp_cmd);
		// 		temp_cmd++;
		// 	}
		// 	temp = temp ->next;
		// }
		// free(res);
    }
    

}
// readline 의 return 은 malloc 된 상태로 나오기 때문에, 호출 후 다 사용하고 나면 free 해줘야 한다. 

// compile : cc -lreadline read_line.c && ./a.out

// readline 의 반환값에는 따옴표도 일반적인 문자처럼 포함되어있음
// 기존 쉘에서는 따옴표를 하나의 문장으로 치환해서 해석하지만
// 여기서는 포함된채 통째로 하나의 큰 문자열로 반환해줌
// 모든것이 날것으로 남아있음