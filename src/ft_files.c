/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:51:37 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/15 23:12:29 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(char *infile, char *outfile, t_pipex *p)
{
	int	flag;

	flag = O_CREAT | O_WRONLY | O_TRUNC;
	p->fdin = open(infile, FLAG_FDIN);
	if (p->fdin < 0)
	{
		if (errno == ENOENT || errno == EACCES)	
			print_err(infile);
	}
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

void	printf_fd(int fd, char *s1, char *s2)
{
	ft_putstr_fd("pipex: ", fd);
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(": ", fd);
	if (errno == EACCES)
		ft_putstr_fd(s2, fd);
	else if (errno == ENOTDIR)
		ft_putstr_fd(s2, fd);
	else
		ft_putstr_fd(s2, fd);
	ft_putstr_fd("\n", fd);
}

int read_and_print_errors(int fd_error)
{
	char buffer[1024];
	ssize_t bytes_read;
	
	bytes_read = read(fd_error, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		write(STDERR_FILENO, buffer, bytes_read);
		bytes_read = read(fd_error, buffer, sizeof(buffer));
	}
	close(fd_error);
	return 0;
}