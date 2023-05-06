/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:05 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:49:06 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	while (*s1_ptr && *s2_ptr)
	{
		if (*s1_ptr != *s2_ptr)
			break ;
		s1_ptr++;
		s2_ptr++;
	}
	if (*s1_ptr > *s2_ptr)
		return (1);
	else if (*s1_ptr == *s2_ptr)
		return (0);
	else
		return (-1);
}
