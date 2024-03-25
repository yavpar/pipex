#include "libft.h"
#include "pipex.h"

int	veriry_files(char *filename, int last_file, t_struct pipex)
{

	pipex->fd_infile = open(filename[1]);
	if (pipex->fd_infile < 0)
	{
		ft_printf("ERROR open() verify file");
		return (1);
	}
	pipex->fd_outfile = open(filename[last_file]); /*lo abre sino, lo crea con flags??*/
	if (pipex->fd_outfile < 0)
		{
			close(pipex->fd_infile);
			ft_printf("ERROR open() verify file");
			return (1);
		}
	return (0);
}

/*	si la forma es de tipo "/path/cmd *args[]" 	*/
/*	crear la linked list de comandos			*/
char	*ft_absolute_path(char **cmds, int len, pipex pipex)
{
	t_cmd	*node;

	node = (t_cmd *)ft_calloc(node, typeof(t_cmd))
	if (!node || (acces(cmd[0], X_OK) < 0))
	{
		ft_free_struc(pipex);
		ft_printf("ERROR acces() or MALLOC abs_path\n");
		exit(1);
	}
	pipex->node->filename = cmd[0]
	if (len == 2)
	{
	}
}
/*	Si la forma es de tipo "cdm *args[]""	*/
/*	crear la linked list de comandos		*/
char *ft_env_path()
{

}
/*	Verifica si el comando es un fichero binario	*/
/*	de tipo:	"cmd *args[]"						*/
/*				"/path/cmd *args[]"					*/
int	verify_executable(char *cmds, char **env, pipex pipex)
{
	char **tab_cmd;
	
	tab_cmd = ft_split(cmd, ' ');
	len = len_tab_cmds(tab_cmds);
	if (ft_strrstr(tab_cmd[0], '/') == 0)
		pipex->path_env = ft_absolute_path(tab_cmd[0], len, pipex);
	else
		pipex->path_env = ft_env_path(tab_cmd[0]);
	else

}

int	ft_parse(int ac, char **av, char **env, pipex *pipex)
{
	int	k;

	if (ac == 5)
	{
		k = 1;
		if (!verify_files(av[k++], ac -1))
			while (k <= ac - 2)
			{
				if (!verify_executable(av[k], env, pipex));
					{
						ft_free_struc();
						ft_printf("ERROR acces()_PARSE");
						return (1);
					}
				k++;
			}
		else
			ft_printF("EROROR open()_PARSE\n");
	}
	else
		;
	return (0);
}
