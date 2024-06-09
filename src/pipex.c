/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:39:26 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/09 14:05:11 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(t_pipex *p);
static void	last_child(t_pipex *p);

int	pipex(t_pipex *p)
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	cmd1 = p->cmd_1;
	cmd2 = p->cmd_2;
	cmd1->pid = fork();
	if (cmd1->pid == -1)
		fatal_error(p, 1);
	if (cmd1->pid == 0)
		first_child(p);
	close(p->tube[WRITE_END]);
	cmd2->pid = fork();
	if (cmd2->pid == -1)
		fatal_error(p, 1);
	if (cmd2->pid == 0)
		last_child(p);
	close(p->tube[READ_END]);
	return (0);
}

/* stdin = 0 stdout = 1*/
static void	first_child(t_pipex *p)
{
	if ((dup2(p->tube[WRITE_END], STDOUT_FILENO)) == -1)
		fatal_error(p, 1);
	if (dup2(p->fdin, STDIN_FILENO) == -1)
		fatal_error(p, 1);
	close_files(4, p->fdin, p->fdout, p->tube[READ_END], p->tube[WRITE_END]);
	execve(p->cmd_1->pathname, p->cmd_1->args, p->env_path);
	print_err(p->cmd_1->args[0]);
	fatal_error(p, 127);
}

static void	last_child(t_pipex *p)
{
	if ((dup2(p->tube[READ_END], STDIN_FILENO)) == -1)
		fatal_error(p, 1);
	if ((dup2(p->fdout, STDOUT_FILENO)) == -1)
		fatal_error(p, 1);
	close_files(2, p->tube[READ_END], p->fdout);
	execve(p->cmd_2->pathname, p->cmd_2->args, p->env_path);
	print_err(p->cmd_2->args[0]);
	fatal_error(p, 127);
}
