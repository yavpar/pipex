/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:35:50 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/15 23:49:53 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	heredoc(char *limiter)
{
	char 	*line;
	int		fd;
	
	if (!limiter)
		return (-1);
	fd = open ("heredoc", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (-1);
	line = get_next_line(0);
	while (line)
	{
		write(1, "> ", 2);
		if ((ft_strlen(line) == ft_strlen(limiter)) &&
			(ft_strncmp(line, limiter, ft_strlen(limiter))))
				break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(fd);
	}
	return (fd);
}
