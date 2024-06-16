/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:39:26 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/15 23:27:17 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(t_pipex *p);
static void	last_child(t_pipex *p);

int	pipex(t_pipex *p)
{	
	if (pipe(p->fd_err) == -1)
		fatal_error(p, 1);
	p->cmd_1->pid = fork();
	if (p->cmd_1->pid == -1)
		fatal_error(p, 1);
	if (p->cmd_1->pid == 0)
		first_child(p);
	close(p->tube[WRITE_END]);
	p->cmd_2->pid = fork();
	if (p->cmd_2->pid == -1)
		fatal_error(p, 1);
	if (p->cmd_2->pid == 0)
		last_child(p);
	close(p->fd_err[WRITE_END]);
	read_and_print_errors(p->fd_err[READ_END]);
	return (0);
}

static void	first_child(t_pipex *p)
{
	close(p->fd_err[READ_END]);
	if ((dup2(p->tube[WRITE_END], STDOUT_FILENO)) == -1)
		fatal_error(p, 1);
	if (dup2(p->fdin, STDIN_FILENO) == -1)
		fatal_error(p, 1);
	close_files(4, p->fdin, p->fdout, p->tube[READ_END], p->tube[WRITE_END]);
	execve(p->cmd_1->pathname, p->cmd_1->args, p->env_path);
	printf_fd(p->fd_err[WRITE_END], p->cmd_1->args[0], strerror(errno));
	fatal_error(p, 127);
}

static void	last_child(t_pipex *p)
{
	close(p->fd_err[READ_END]);
	if ((dup2(p->tube[READ_END], STDIN_FILENO)) == -1)
		fatal_error(p, 1);
	if ((dup2(p->fdout, STDOUT_FILENO)) == -1)
		fatal_error(p, 1);
	close_files(4, p->fdin, p->fdout, p->tube[READ_END], p->tube[WRITE_END]);
	execve(p->cmd_2->pathname, p->cmd_2->args, p->env_path);
	printf_fd(p->fd_err[WRITE_END], p->cmd_2->args[0], strerror(errno));
	fatal_error(p, 127);
}
