/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:46 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/03 12:32:49 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	free_center(t_data *data)
{
	free_array(data->cmd_options[0], 1);
	free_array(data->cmd_options[1], 1);
	free(data->cmd[0]);
	free(data->cmd[1]);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_err_msg(ac != 5, "Invalid number of arguments", __FILE_NAME__, __LINE__);
	pipex_set(av, env, &data);
	pipex_execute(&data, env);
	free_center(&data);
	return (EXIT_SUCCESS);
}
