#include "mini_builtin.h"

void	print_variable(char *str)
{
	char	*point;
	char	*key;
	char	*value;
	char	*line;

	point = ft_strchr(str, '=');
	key = ft_substr(str, 0, point - str + 1);
	if (!key)
		exit(EXIT_FAILURE);
	value = ft_substr(str, point - str + 1, ft_strlen(str));
	if (!value)
		exit(EXIT_FAILURE);
	line = ft_strjoin(value, "\"");
	if (!line)
		exit(EXIT_FAILURE);
	ft_putstr_fd("export ", 1);
	ft_putstr_fd(key, 1);
	ft_putchar_fd('\"', 1);
	ft_putendl_fd(line, 1);
	free(key);
	free(value);
	free(line);
}
