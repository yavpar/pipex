/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:58 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/11 19:11:44 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_child1(t_pipex *p);
static void	free_child2(t_pipex *p);

void	fatal_error(t_pipex *p, int err)
{
	close_files(4, p->fdin, p->fdout, p->tube[WRITE_END], p->tube[READ_END]);
	destroy_list(p);
	exit(err);
}

void	print_err(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	destroy_list(t_pipex *p)
{
	int	k;

	k = 0;
	if (p->cmd_1)
		free_child1(p);
	if (p->cmd_2)
		free_child2(p);
	if (p->env_path)
	{
		while (p->env_path[k])
		{
			free(p->env_path[k]);
			k++;
		}
		free(p->env_path);
		p->env_path = NULL;
	}
}

static void	free_child1(t_pipex *p)
{
	int	k;

	k = 0;
	if (p->cmd_1->args)
	{
		while (p->cmd_1->args[k])
		{
			free(p->cmd_1->args[k]);
			k++;
		}
		free(p->cmd_1->args);
		if (p->access1)
			free(p->cmd_1->pathname);
	}
	free(p->cmd_1);
	p->cmd_1 = NULL;
}

static void	free_child2(t_pipex *p)
{
	int	k;

	k = 0;
	if (p->cmd_2->args)
	{
		while (p->cmd_2->args[k])
		{
			free(p->cmd_2->args[k]);
			k++;
		}
		free(p->cmd_2->args);
		if (p->access2)
			free(p->cmd_2->pathname);
	}
	free(p->cmd_2);
	p->cmd_2 = NULL;
}
