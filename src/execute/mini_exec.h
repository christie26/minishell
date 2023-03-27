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



typedef struct t_process {
    int     order; 
    int     read_fd; // 0 -> STDIO / 1 -> pipe / 2 -> file 
    char    *read_file; // if read == 1or2 it's NULL
    int     write_fd; // 0 -> STDIO / 1 -> pipe / 2 -> file 
    char    *write_file; // if read == 1or2 it's NULL
    char    *cmd;
    char    **options;
}   s_process;

/*
cat | grep a > file1 

cat {
    int order = 0;
    int read = 0; //STDIN
    char *read_file = NULL;
    int write = 1; //pipe
    char *write_file = NULL;
    char *cmd = cat;
    char **options = ???;
}

grep {
    int order = 1;
    int read = 1; //pipe
    char *read_file = NULL;
    int write = 2; // fie
    char *write_file = file1; (str 그대로)
    char *cmd = grep;
    char **options = a 관련;
}
*/

int mini_echo(char *file, int option);

#endif
