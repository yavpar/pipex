/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:39:26 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/11 17:53:49 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_pipex *pipex, t_list *cmds_list)
{
	int		k;
	t_list	*cmd;

	k = 1;
	cmd = cmds_list;
	while (k <= pipex->cmds)
	{
		if (pipe(((t_cmd *)cmd->content)->tube) == -1)
			destroy_list(pipex, cmds_list);
		((t_cmd *)cmd->content)->pid = fork();
		if (((t_cmd *)cmd->content)->pid == -1)
			destroy_list(pipex, cmds_list);
		if (((t_cmd *)cmd->content)->pid == 0)
			child_process(pipex, cmds_list, k);
		else
		{
			if (close(((t_cmd *)cmd->content)->tube[1] == -1))
				destroy_list(pipex, cmds_list);
			if (cmd->next != NULL)
				cmd = cmd->next;
		}
		k++;
	}
}

void	child_process(t_pipex *pipex, t_list *cmd_struct, int cmd)
{
	if (cmd == 1)
		first_child(pipex, cmd_struct);
	else if (cmd - 1 == 0)
		last_child(pipex, cmd_struct);
}
/* stdin = 0 stdout = 1*/
void	first_child(t_pipex *pipex, t_list *cmd)
{
	if (dup2(((t_cmd *)cmd->content)->tube[1], STDOUT_FILENO) == -1)
		destroy_list(pipex, cmd);
	if (close(((t_cmd *)cmd->content)->tube[0]) == -1)
		destroy_list(pipex, cmd);
	if (dup2(pipex->fd_infile, STDIN_FILENO) == -1)
		destroy_list(pipex, cmd);
	if (close(pipex->fd_infile) == -1)
		destroy_list(pipex, cmd);
	if (execve(((t_cmd *)cmd->content)->filename, ((t_cmd *)cmd->content)->args,
			pipex->env_path))
		destroy_list(pipex, cmd);
}
