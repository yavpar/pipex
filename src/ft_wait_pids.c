/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_pids.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:15:42 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/27 12:55:42 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_pids(t_pipex *p)
{
	int	wstatus1;
	int	wstatus2;
	int	exit_status;

	waitpid(p->cmd_1->pid, &wstatus1, WUNTRACED);
	waitpid(p->cmd_2->pid, &wstatus2, WUNTRACED);
	if (WIFEXITED(wstatus2))
	{
		exit_status = WEXITSTATUS(wstatus2);
		return (exit_status);
	}
	return (0);
}
