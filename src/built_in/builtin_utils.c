#include "built_in.h"

void	print_variable(char *str)
{
	char	*point;
	char	*key;
	char	*value;
	char	*line;

	point = ft_strchr(str, '=');
	key = ft_substr(str, 0, point - str + 1);
	ft_err_msg_exit(!key, MALLOC_ERROR, __FILE__, __LINE__);
	value = ft_substr(str, point - str + 1, ft_strlen(str));
	ft_err_msg_exit(!value, MALLOC_ERROR, __FILE__, __LINE__);
	line = ft_strjoin(value, "\"");
	ft_err_msg_exit(!line, MALLOC_ERROR, __FILE__, __LINE__);
	ft_putstr_fd("export ", 1);
	ft_putstr_fd(key, 1);
	ft_putchar_fd('\"', 1);
	ft_putendl_fd(line, 1);
	free(key);
	free(value);
	free(line);
}
