/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:58 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/16 16:25:51 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_child1(t_pipex *p);
static void	free_child2(t_pipex *p);
static void	free_envp(t_pipex *p);

void	destroy_list(t_pipex *p)
{
	if (p->cmd_1)
		free_child1(p);
	if (p->cmd_2)
		free_child2(p);
	if (p->env_path)
		free_envp(p);
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

static void	free_envp(t_pipex *p)
{
	int	k;

	k = 0;
	while (p->env_path[k])
	{
		free(p->env_path[k]);
		k++;
	}
	free(p->env_path);
	p->env_path = NULL;
}
