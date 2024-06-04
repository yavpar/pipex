/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:51:37 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/27 16:59:22 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(char *infile, char *outfile, t_pipex *p)
{
	p->fd_infile = open(infile, FLAG_FDIN);
	if (p->fd_infile < 0)
		ft_printf("%s\n", INFILE_ERR);
	p->fd_outfile = open(outfile, FLAG_FDOUT, 0644);
	if (p->fd_outfile < 0)
	{
		ft_printf("%s\n", OUTFILE_ERR);
		if (p->fd_infile > 0)
			close(p->fd_infile);
	}
	if (p->fd_infile < 0)
	{
		close_files(p);
		return (1);
	}
	return (0);
}

void	close_files(t_pipex *p)
{
	if (p->fd_infile > 0)
		close(p->fd_infile);
	if (p->fd_outfile > 0)
		close(p->fd_outfile);
}
