/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:02 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/11 15:32:46 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int ac, char **av, char **envp)
{
	t_pipex	*pipex;


	pipex = NULL;
	if (ac != 5)
	{
		printf("Not enough arguments to run this program:\n");
		printf("Format: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	//ft_init_var();
printf("Commance PARSE\n");
	parse(ac, av, envp, pipex);

printf("Parse OK\n");
	//ft_pipex(pipex);

	return (0);
}


// int	veriry_files(char *filename, int last_file, t_pipex *pipex)
// {

// 	if (filename)
// 	{
// 		pipex->fd_infile = open(filename[1], FLAG_FDIN);
// 		if (pipex->fd_infile < 0)
// 		{
// 			ft_printf("ERROR open() verify file");
// 			return (1);
// 		}
// 		pipex->fd_outfile = open(filename[last_file], FLAG_FDOUT); /*lo abre sino, lo crea con flags??*/
// 		if (pipex->fd_outfile < 0)
// 			{
// 				close(pipex->fd_infile);
// 				ft_printf("ERROR open() verify file");
// 				return (1);
// 			}
// 	}
// 	return (0);
// }

// /*	si la forma es de tipo "/path/cmd *args[]" 	*/
// /*	crear la linked list de comandos			*/
// char	*ft_absolute_path(char **cmds, int len, t_pipex pipex)
// {
// 	t_cmd	*node;

// 	node = (t_cmd *)ft_calloc(node, typeof(t_cmd));
// 	if (!node || (acces(cmd[0], X_OK) < 0))
// 	{
// 		ft_free_struc(pipex);
// 		ft_printf("ERROR acces() or MALLOC abs_path\n");
// 		exit(1);
// 	}
// 	pipex->node->filename = cmd[0];
// 	if (len == 2)
// 	{
// 	}
// }
// /*	Si la forma es de tipo "cdm *args[]""	*/
// /*	crear la linked list de comandos		*/
// char *ft_env_path(char **env, t_pipex *pipex)
// {
// 	int	k;
// 	char	*new_env;

// 	k = 0;
// 	while (env[k])
// 	{
// 		if (strncmp("PATH=", env[k], 5) == 0)
// 		{
// 			new_env = env[k];
// 			new_env = new_env + 5;
// 			break ;
// 		}
// 		k++;
// 	}
// 	k = 0;
// 	envp = ft_split(new_env, ':');
// 	while (envp[k])
// 	{
// 		printf("%s\n", envp[k]);
// 		k++;
// 	}
// 	k = 0;
// 	while (envp[k])
// 		k++;
// 	ft_free_array((void **)envp, k, (void (*)(void *))ft_free);

// }
// /*	Verifica si el comando es un fichero binario	*/
// /*	de tipo:	"cmd *args[]"						*/
// /*				"/path/cmd *args[]"					*/
// int	verify_executable(char *cmds, char **env, t_pipex *pipex)
// {
// 	char **tab_cmd;

// 	tab_cmd = ft_split(cmd, ' ');
// 	len = len_tab_cmds(tab_cmds);
// 	if (ft_strrstr(tab_cmd[0], '/') == 0)
// 		pipex->path_env = ft_absolute_path(tab_cmd[0], len, pipex);
// 	else
// 		pipex->path_env = ft_env_path(tab_cmd[0]);

// }
// //
// //
// //

// int	get_envp(char **env, t_pipex *pipex)
// {
// 	char *path;
// 	int	k;

// 	k = 0;
// 	path = NULL;
// 	while (env[k])
// 	{
// 		if (ft_strncmp(env[k], "PATH=", 5) == 0)
// 		{
// 			path = env[k];
// 			path = path + 5;
// 			break ;
// 		}
// 		k++;
// 	}
// 		return (1);
// 	pipex->env_path = ft_split(path, ':');
// 	if (pipex->env_path == NULL)
// 		return (1);
// 	return (0);
// }

// //
// //
// //





