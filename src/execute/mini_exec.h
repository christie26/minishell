/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:47:19 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/24 20:53:01 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H

# define MINI_EXEC_H

# include <stdio.h>

typedef struct t_execute {
    int     order;
    int     fd_read;
    int     fd_write;
    char    *cmd;
    char    **options;
}   s_execute;


int mini_echo(char *file, int option);

#endif
