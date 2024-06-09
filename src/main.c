/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:02 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/09 14:07:20 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;
	int		ws;

	ws = 0;
	p.cmd_1 = NULL;
	p.cmd_2 = NULL;
	if (ac != 5)
		(ft_printf("%s%s", INPUT_ERR1, INPUT_ERR2), exit(1));
	parse(ac, av, envp, &p);
	if (pipe(p.tube) < -1)
	{
		perror("pipe: ");
		return (destroy_list(&p), 1);
	}
	pipex(&p);
	ft_printf("En MAIN:\n");
	close_files(4,p.fdin, p.fdout, p.tube[0], p.tube[1]);
	ws = wait_pids(&p);
	destroy_list(&p);
	return (ws);
}
