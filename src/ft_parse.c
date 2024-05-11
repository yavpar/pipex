/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:12:17 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/11 16:02:00 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_envp(char **env, t_pipex *pipex);        /* Create a char** of PATH	*/
int	get_cmds(int ac, char **av, t_pipex *pipex); /**/
void	create_cmd_list(t_pipex *pipex, t_cmd *cmd_struct, int cmd);
t_cmd	*set_cmd_env(t_pipex *pipex, t_cmd *cmd_struct);
int		open_files(char *in_file, char *out_file, t_pipex *pipex);

int	parse(int ac, char **av, char **envp, t_pipex *pipex)
{
printf("At the biginning of PARSE\n");
	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		exit(1);
	if (open_files(av[1], av[4], pipex)== 0)
	{
		free(pipex);
		exit(1);
	}
printf("Open files OK\n");
	if (get_envp(envp, pipex) == 0)
	{
		//close_files(pipex->fd_infile, pipex->fd_outfile);
		free(pipex);
		exit(1);
	}
printf("get envp OK\n");
	if (get_cmds(ac, av + 2, pipex) == 0)
	{
		//close_files(pipex->fd_infile, pipex->fd_outfile);
		ft_free_array((void **)pipex->env_path, ft_len_tab(pipex->env_path),
			(void (*)(void *))ft_free);
		free(pipex);
		exit(1);
	}
printf("get cmds OK\n");
printf("At the end of PARSE\n");
	return (0);
}

int	get_envp(char **env, t_pipex *pipex)
{
	char	*path;
	int		k;
printf("En la funcion [get_envp]\n");
	k = 0;
	pipex->env_path = NULL;
	path = NULL;
	while (env[k])
	{
		if (ft_strncmp(env[k], "PATH=", 5) == 0)
		{
			path = env[k];
			path = path + 5;
			break ;
		}
		k++;
	}
	pipex->env_path = split_add_slash(path, ':');
	if (pipex->env_path == NULL)
	{
		printf("ERROR: split environement\n");
		return (0);
	}
printf("Fin de la funcion [get_envp]\n");
	return (1);
}

/*	This function take the struct of the command and adds it	*/
/*	to the linked list											*/

void	create_cmd_list(t_pipex *pipex, t_cmd *cmd_struct, int cmd)
{
	// int k = 0;
	// static int n = 0;
	if (ft_char_in_str(cmd_struct->args[0], '/') == 1)
		cmd_struct->filename = cmd_struct->args[0];
	else
	{
		set_cmd_env(pipex, cmd_struct);
		if (cmd == 0)
			pipex->cmds_list = ft_lstnew(cmd_struct);
		else
			ft_lstadd_back(&pipex->cmds_list, ft_lstnew(cmd_struct));
	}
	// IMPRESION DE COMANDOS
// n++;
// printf("\t\t\tComando numero [%d]\n", n);

// printf("Filename = %s\n", cmd_struct->filename);
// 		while (cmd_struct->args[k])
// 		{
// printf("*arg[] = %s\n",cmd_struct->args[k]);
// 			k++;
// 		}



}

/*	This function creates a linked list, each pointer points	*/
/*	to another struct that contains the variables to use		*/
/*	for EXECVE funtion. 										*/

int	get_cmds(int ac, char **av, t_pipex *pipex)
{
	int		k;
	t_cmd	*cmd_struct;


	k = 0;
	pipex->cmds = ac - 3;
printf("En la funcion [get_cmds]\n");
	while (k < pipex->cmds)
	{
		cmd_struct = (t_cmd *)malloc(sizeof(t_cmd));
		if (cmd_struct == NULL)
		{
			//distroy_list(pipex, cmd_struct);// crear funcion para liberar memoria de el array y las estructuras;
			exit(1);
		}
		cmd_struct->args = ft_split(av[k], ' ');
		if (cmd_struct->args == NULL)
		{
			//distroy_list(pipex, cmd_struct); // y el las estructuras
			exit(1);
		}
		create_cmd_list(pipex, cmd_struct, k);
		k++;
	}
	// para imprimir la lista de comandos //
	//n = 0;
	//temp = pipex->cmds_list;
	// while (n > pipex->cmds)
	// {
	// 	k = 0;
	// 	printf("Filename = %s\n", ((t_cmd *)temp->content)->filename);
	// 	while (((t_cmd *)temp->content)->args[k])
	// 	{
	// 		printf("\t\t\t*arg[%d] = %s\n\n", k + 1,((t_cmd *)temp->content)->args[k]);
	// 		k++;
	// 	}
	// 	temp = temp->next;
	// 	n--;
	// }
	// fin de impresion //
	return (1);
}

/*	This function defines "filename" and "*args[]"	*/

t_cmd	*set_cmd_env(t_pipex *pipex, t_cmd *cmd_struct)
{
printf("En la funcion [set_cmd_env]\n");
	int		k;
	char	*cmd;

	k = 0;
	while (pipex->env_path[k])
	{
		cmd = ft_strjoin(pipex->env_path[k], cmd_struct->args[0]);
		if (cmd == NULL)
		{
			//distroy_list(pipex, pipex->cmds_list);
			return NULL;
		}
		if (access(cmd, X_OK) == 0)
		{
			cmd_struct->filename = cmd; /* si tengo acceso, apunto a la nueva direccion*/
			free(cmd_struct->args[0]);/* libero la memoria del nombre del comando*/
			cmd_struct->args[0] = cmd;/* asigno el nuevo comando con el path adecuado */
			return (cmd_struct); /* salgo de la bucle */
		}
		free(cmd);
		k++;
	}
	cmd_struct->filename = cmd_struct->args[0];
	return (cmd_struct);
}

int	open_files(char *in_file, char *out_file, t_pipex *pipex)
{
printf("En la funcion [open_files]\n");

	pipex->fd_infile = open(in_file, FLAG_FDIN);
	if (pipex->fd_infile < 0)
		printf("ERROR open_infile\nMessage: %s\n\n", strerror(errno));
	pipex->fd_outfile = open(out_file, FLAG_FDOUT, 0644);
	if (pipex->fd_outfile < 0)
		printf("ERROR open_outfile\nMessage: %s\n", strerror(errno));
	if (pipex->fd_infile == -1 || pipex->fd_outfile == -1)
	{
		if (close(pipex->fd_infile) < 0)
			printf("Error close infile\nMessage: %s\n\n", strerror(errno));
		if (close(pipex->fd_outfile) < 0)
			printf("Error close outfile\nMessage: %s\n\n", strerror(errno));
		return (0);
	}
	return (1);
}
