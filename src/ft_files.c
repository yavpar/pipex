/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:51:37 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/09 14:11:14 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(char *infile, char *outfile, t_pipex *p)
{
	int	flag;

	flag = O_CREAT | O_WRONLY | O_TRUNC;
	p->fdin = open(infile, FLAG_FDIN);
	if (p->fdin < 0)
		print_err(infile);
	p->fdout = open(outfile, flag, 0644);
	if (p->fdout < 0)
		print_err(outfile);
}

void	close_files(int n, ...)
{
	va_list	fds;
	int		k;

	k = 0;
	va_start(fds, n);
	while (k < n)
	{
		close(va_arg(fds, int));
		k++;
	}
	va_end(fds);
}
