/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_pids.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:15:42 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/17 18:31:26 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_pids(t_pipex *p)
{
	int	wstatus;
	
	if (waitpid(p->cmd_1->pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
		perror("waitpid");
	if (waitpid(p->cmd_2->pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
		perror("waitpid");
}