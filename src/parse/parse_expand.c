/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:52:05 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 20:33:45 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parse.h"

char	*get_key_from_word(char **str)
{
	int		brace;
	char	*substr_offset;
	char	*key;

	brace = (**str == '{');
	if (brace)
		++*str;
	substr_offset = *str;
	while (ft_isalnum(**str))
		++*str;
	if (brace)
	{
		if (**str == '\0')
			error_command_msg("parse", BRACE_ERROR);
		else if (**str != '}' || *str - substr_offset == 0)
			error_command_msg("parse", BAD_SUB_ERROR);
		return (NULL);
	}
	key = ft_substr(substr_offset, 0, *str - substr_offset);
	if (key == NULL)
		exit(EXIT_FAILURE);
	if (brace)
		++*str;
	return (key);
}

char	*get_expanded_word2(char **str, char **my_env)
{
	char	*key;
	char	*result;

	key = get_key_from_word(str);
	if (key == NULL)
		return (NULL);
	result = get_value(key, my_env);
	free(key);
	return (result);
}

char	*get_expanded_word(char **str, char **my_env)
{
	char	check;

	check = *(*str + 1);
	if (ft_isalnum(check) || check == '{')
	{
		++*str;
		return (get_expanded_word2(str, my_env));
	}
	else if (check == '?')
	{
		++*str;
		++*str;
		return (ft_itoa(g_exit_status));
	}
	else
		return (get_non_expanded_word(str));
}

char	*get_non_expanded_word(char **str)
{
	char	open_quote;
	char	*substr_offset;
	char	*word;

	substr_offset = *str;
	open_quote = '\0';
	if (**str == '$')
		++*str;
	while (**str)
	{
		if (!open_quote && is_quote(**str))
			open_quote = **str;
		else if (open_quote && open_quote == **str)
			open_quote = '\0';
		if (**str == '$' && open_quote != '\'')
			break ;
		++*str;
	}
	word = ft_substr(substr_offset, 0, *str - substr_offset);
	if (word == NULL)
		exit(EXIT_FAILURE);
	return (word);
}

char	*get_expanded_string(char *str, char **my_env)
{
	t_list	*word_list;
	t_list	*new_word;
	char	*content;

	word_list = NULL;
	while (*str)
	{
		if (*str == '$')
		{
			content = get_expanded_word(&str, my_env);
			if (content == NULL)
			{
				ft_lstclear(&word_list, free);
				return (NULL);
			}
		}
		else
			content = get_non_expanded_word(&str);
		new_word = ft_lstnew(content);
		if (new_word == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&word_list, new_word);
	}
	return (word_list_join(word_list));
}
