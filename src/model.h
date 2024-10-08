/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:16 by yoonsele          #+#    #+#             */
/*   Updated: 2023/05/05 18:49:27 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_H

# define MODEL_H

# include <unistd.h>

int	g_exit_status;

typedef struct s_redirect {
	int					type;
	char				*filename;	
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd_block {
	t_redirect	*redirect;
	char		**cmd;
}	t_cmd_block;

typedef struct s_pipeline {
	t_cmd_block			*cmd_block;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_data {
	int		process_number;
	int		prev_fd;
	char	**path;
	char	**my_env;
}	t_data;

#endif