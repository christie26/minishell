/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:47:00 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/24 21:49:19 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_exec.h"

int mini_echo(char *file, int option)
{
    if (option)
    {
        printf("I want to execute echo with option\n");
        printf("parameter is %s\n", file);
    }
    else   
    {
        printf("I want to execute echo without option\n");
        printf("parameter is %s\n", file);
    }
	return (0);
}
