#include "libft.h"
#include "pipex.h"

int	veriry_files(char *filename, int last_file, t_struct pipex)
{

	if (filename)
	{
		pipex->fd_infile = open(filename[1], O_RDONLY);
		if (pipex->fd_infile < 0)
		{
			ft_printf("ERROR open() verify file");
			return (1);
		}
		pipex->fd_outfile = open(filename[last_file], O_RWONLY | O_CREATE | O_TRUNC); /*lo abre sino, lo crea con flags??*/
		if (pipex->fd_outfile < 0)
			{
				close(pipex->fd_infile);
				ft_printf("ERROR open() verify file");
				return (1);
			}
	}
	return (0);
}

/*	si la forma es de tipo "/path/cmd *args[]" 	*/
/*	crear la linked list de comandos			*/
char	*ft_absolute_path(char **cmds, int len, t_pipex pipex)
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
char *ft_env_path(char **env, t_pipex *pipex)
{
	int	k;

	k = 0;
	while (env[k])
	{
		if (strncmp("PATH=", env[k], 5) == 0)
		{
			new_env = env[k];
			new_env = new_env + 5;
			break ;
		}
		k++;
	}
	k = 0;
	envp = ft_split(new_env, ':');
	while (envp[k])
	{
		printf("%s\n", envp[k]);
		k++;
	}
	k = 0;
	while (envp[k])
		k++;
	ft_free_array((void **)envp, k, (void (*)(void *))ft_free);

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

}

int	ft_parse(int ac, char **av, char **env, pipex *pipex)
{
	int	k;

	if (ac == 5)
	{
		k = 1;
		if (!verify_files(av[k++], ac - 1))
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
			ft_printf("EROROR open()_PARSE\n");
	}
	else
		;
	return (0);
}
//
//
//

int	get_envp(char **env, t_pipex *pipex)
{
	char *path;
	int	k;
	
	k = 0;
	path = NULL;
	while (env[k])
	{
		if (strncmp(env[k], "PATH=", 5) == 0)
		{
			path = env[k];
			path = path + 5;
			break ;
		}
		k++;
	}
		return (1);
	pipex->env_path = ft_split(path, ':');
	if (pipex->env_path == NULL)
		return (1);
	return (0);
}

//
//
//


int	ft_open_files(char *in_file, char *out_file, t_pipex *pipex)
{
	int	fd_infile;
	int	fd_outfile;

	fd_infile = open(in_file, FLAG_FDIN);
	if (fd_infile < 0)
	{
		printf("ERROR open_infile()\n");
		printf("errno value: %d\n", errno);
		printf("Error message: %s\n\n", strerror(errno));
	}
	fd_outfile = open(out_file, FLAG_FDOUT, 0644);
	if (fd_outfile < 0)
	{
		printf("ERROR open_outfile()\n");
		printf("errno value: %d\n", errno);
		printf("Error message: %s\n", strerror(errno));
	}
	if (fd_infile == -1 || fd_outfile == -1)
	{
		if (close(fd_infile) < 0)
		{
			printf("error close infile\n");
			printf("errno value: %d\n", errno);
			printf("Error message: %s\n\n", strerror(errno));
		}
		if (close(fd_outfile) < 0)
		{
			printf("error close infile\n");
			printf("errno value: %d\n", errno);
			printf("Error message: %s\n\n", strerror(errno));
		}
		return (-1);
	}
	return (0);
}

//
//
//

#include "pipex.h"

char	**ft_split(char *s, char sep);
void	ft_free_array(void **s, int size_s, void(ft_free)(void *));
void	ft_free(void *data);
char	*ft_strjoin(char const *s1, char const *s2);
int	get_envp(char **env, t_pipex *pipex);

int get_cmd(int ac, char **av, t_pipex *pipex)
{
	int k;
	char *filename;
	char *flags[2];
	char **path_env;

	if (av)
		;
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	flags[0] = "pwd";
	//flags[1] = "-la";
	//flags[2] = "";
	flags[1] = NULL;
	if (get_envp(envp, pipex) != 0)
	{
        perror("get_envp");
        exit(EXIT_FAILURE);
	}
	//k = 0;
	filename = flags[0];
	// while (pipex->env_path[k])
	// {
	// 	filename = ft_strjoin(pipex->env_path[k], flags[0]);
	// 	if ((access(filename, F_OK ) == 0) && (access(filename, X_OK) == 0))
	// 	{
	// 		printf("La ruta [%s] SI es valida para el comando [%s]\n", pipex->env_path[k], flags[0]);
	// 		break ;
	// 	}
	// 	else
	// 		printf("La ruta [%s] NO es valida para el comando [%s]\n", pipex->env_path[k], flags[0]);
	// 	free (filename);
	// 	filename = NULL;
	// 	k++;
	// }
	execve(filename, flags, pipex->env_path);
	perror("execve"); // Imprime un mensaje de error basado en errno
	printf("Valor de errno: %d\n", errno);
	printf("Mensaje de error: %s\n", strerror(errno));
	k = 0;
	// if (filename)
	// 	free(filename);
	while (pipex->env_path[k])
		k++;
	ft_free_array((void **)pipex->env_path, k,
						(void (*)(void *))ft_free);
	return (1);
}

//
//
//

int main (int ac, char **av, char **envp) 
{
	t_pipex *pipex;

	pipex = NULL;
	if (ac != 5)
	{
		printf("Not enough arguments to run this program:\n");
		printf("Format: ./pipex file1 cmd1 cmd2 [...] file2\n")
		return (1);
	}
	ft_init_var();
	ft_parse(ac, av, envp, pipex);
	return (0);
}

    // if (argc > 1) {
    //     char * word = strtok (argv[1], " ");
    //     char path[128] = "/bin/";
    //     strcat (path, word);

    //     char * newenvp[] = { NULL };
    //     char * newargv[] = { path, NULL };
    //     printf ("[%s]\n", path);
    //     int ret = execve (path, newargv, newenvp);
    //     if (ret == -1) {
    //         perror("execve error");
    //     }
    // }
    // return 0;
