/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:39:26 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/27 17:36:33 by yparthen         ###   ########.fr       */
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
	if (pipe(p->tube) == -1)
		(close_files(p), destroy_list(p), exit(8));
	cmd1->pid = fork();
	if (cmd1->pid == -1)
		(close_files(p), destroy_list(p), exit(9));
	if (cmd1->pid == 0)
		first_child(p);
	if (close(p->tube[WRITE_END]) == 1)
		(close_files(p), destroy_list(p), exit(10));
	cmd2->pid = fork();
	if (cmd2->pid == -1)
		(perror(FORK2_ERR), exit(10));
	if (cmd2->pid == 0)
		last_child(p);
	if (close(p->tube[READ_END]) == -1)
		destroy_list(p);
	return (0);
}

/* stdin = 0 stdout = 1*/
static void	first_child(t_pipex *p)
{
	if (close(p->tube[READ_END]) == -1)
		destroy_list(p);
	if (dup2(p->tube[WRITE_END], STDOUT_FILENO) == -1)
		destroy_list(p);
	if (dup2(p->fd_infile, STDIN_FILENO) == -1)
		destroy_list(p);
	if (close(p->fd_infile) == -1)
		destroy_list(p);
	if (close(p->tube[WRITE_END]) == -1)
		destroy_list(p);
	execve(p->cmd_1->pathname, p->cmd_1->args, p->env_path);
	close_files(p);
	destroy_list(p);
	perror("execve cmd1");
	exit(127);
}

static void	last_child(t_pipex *p)
{
	if (dup2(p->tube[READ_END], STDIN_FILENO) == -1)
		destroy_list(p);
	if (dup2(p->fd_outfile, STDOUT_FILENO) == -1)
		destroy_list(p);
	if (close(p->tube[READ_END]) == -1)
		destroy_list(p);
	if (close(p->fd_outfile) == -1)
		destroy_list(p);
	execve(p->cmd_2->pathname, p->cmd_2->args, p->env_path);
	close_files(p);
	destroy_list(p);
	perror("execve cmd2");
	exit(127);
}
/*
int	pipex(t_pipex *p)
{
	int		k;
	t_list	*cmd;

	cmd = p->cmds_list;
	int fd_prev_read = p->fd_infile;
		// Descriptor de archivo para leer desde el archivo de entrada inicial
	for (k = 1; k <= p->cmds; k++)
	{
		int pipe_fd[2];
			// Array para almacenar los descriptores de archivo del pipe
		// Crear el pipe
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid_t pid = fork(); // Crear un nuevo proceso hijo
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0) // Proceso hijo
		{
			close(pipe_fd[0]); // Cerrar el extremo de lectura del pipe
			if (k == 1) // Primer comando
			{
				// Redirigir la salida estándar al extremo de escritura del pipe
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					return (1);
				}
			}
			else if (k == p->cmds) // Último comando
			{
				// Redirigir la entrada estándar desde el extremo de lectura del pipe
				if (dup2(fd_prev_read, STDIN_FILENO) == -1)
				{
					perror("dup2");
					return (1);
				}
			}
			else // Comandos intermedios
			{
				// Redirigir la entrada estándar desde el extremo de lectura del pipe anterior
				if (dup2(fd_prev_read, STDIN_FILENO) == -1)
				{
					perror("dup2");
					return (1);
				}
				// Redirigir la salida estándar al extremo de escritura del pipe
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					return (1);
				}
			}
			// Cerrar descriptores de archivo no necesarios
			close(pipe_fd[1]);
			close(fd_prev_read);
			// Ejecutar el comando
			execve(((t_cmd *)cmd->content)->filename,
				((t_cmd *)cmd->content)->args, p->env_path);
			// Si execve falla, imprimir un mensaje de error
			perror("execve");
			return (1);
		}
		else // Proceso padre
		{
			close(pipe_fd[1]);
				// Cerrar el extremo de escritura del pipe en el proceso padre
			// Si no es el primer comando,
				cerrar el descriptor de archivo de lectura anterior
			if (k != 1)
				close(fd_prev_read);
			// Guardar el descriptor de archivo de lectura para el próximo comando
			fd_prev_read = pipe_fd[0];
			// Mover al siguiente comando en la lista
			cmd = cmd->next;
		}
	}
	// Esperar a que todos los procesos hijos terminen
	for (k = 0; k < p->cmds; k++)
	{
		if (wait(NULL) == -1)
		{
			perror("wait");
			return (1);
		}
	}
	return (0);
}
*/
