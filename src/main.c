/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:02 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/15 18:57:20 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_var(t_pipex *p);

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;
	int		ws;

	ws = 0;
	init_var(&p);
	if (ac != 5)
		(ft_printf("%s%s", INPUT_ERR1, INPUT_ERR2), exit(1));
	parse(ac, av, envp, &p);
	if (pipe(p.tube) < -1)
	{
		perror("pipex: pipe ");
		return (destroy_list(&p), 1);
	}
	pipex(&p);
	close_files(4, p.fdin, p.fdout, p.tube[0], p.tube[1]);
	ws = wait_pids(&p);
	destroy_list(&p);
	return (ws);
}

static void	init_var(t_pipex *p)
{
	p->tube[0] = -1;
	p->tube[1] = -1;
	p->fd_err[0] = -1;
	p->fd_err[1] = -1;
	p->fdin = -1;
	p->fdout = -1;
	p->env_path = NULL;
	p->cmd_1 = NULL;
	p->cmd_2 = NULL;
	p->access1 = -1;
	p->access2 = -1;
	p->arg1 = NULL;
	p->arg2 = NULL;
}
