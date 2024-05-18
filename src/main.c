/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:02 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/18 19:03:44 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;
	
	if (ac != 5)
		(ft_printf("%s%s", INPUT_ERR1, INPUT_ERR2), exit (1));
	parse(ac, av, envp, &p);
	if (pipe(p.tube) < -1)
	{
		ft_printf("%s", PIPE_ERR);
		return (destroy_list(&p), 6);
	}
	pipex(&p);
	close_files(&p);
	wait_pids(&p);
	destroy_list(&p);
	return (EXIT_SUCCESS);
}
