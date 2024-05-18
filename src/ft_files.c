/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:51:37 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/18 18:44:16 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(char *infile, char *outfile, t_pipex *pipex)
{
	pipex->fd_infile = open(infile, FLAG_FDIN);
	if (pipex->fd_infile < 0)
	{
		ft_printf("%s\n", INFILE_ERR);
		return (1);	
	}
	pipex->fd_outfile = open(outfile, FLAG_FDOUT, 0644);
	if (pipex->fd_outfile < 0)
	{	
		ft_printf("%s\n", OUTFILE_ERR);
		if (close(pipex->fd_infile) < 0)
			ft_printf("Error close infile\n");
		return (1);
	}
	return (0);
}

void	close_files(t_pipex *p)
{
	if (close(p->fd_infile) == -1)
		perror("close infile");
	if (close(p->fd_outfile) == -1)
		perror("close outfile");
}