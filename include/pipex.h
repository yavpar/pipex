#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define FLAG_FDIN (O_RDONLY)
# define FLAG_FDOUT (O_CREAT | O_WRONLY | O_TRUNC)

typedef struct s_pipex
{
	int	fd_infile;
	int	fd_outfile;
	char	**env_path;
	t_list	*cmds_list;
	int		cmds;
}			t_pipex;

typedef struct s_cmd
{
	char	**args;
	char	*filename;
	int		tube[2];
	int		pid;
}			t_cmd;

/*	FOR PARSING ARGUMENTS	*/

int	parse(int ac, char **av, char **envp, t_pipex *pipex);
int	get_envp(char **env, t_pipex *pipex);        /* Create a char** of PATH	*/
int	get_cmds(int ac, char **av, t_pipex *pipex); /**/
void	create_cmd_list(t_pipex *pipex, t_cmd *cmd_struct, int cmd);
t_cmd	*set_cmd_env(t_pipex *pipex, t_cmd *cmd_struct);
int		open_files(char *in_file, char *out_file, t_pipex *pipex);


/*	UTILS*/

char	**split_add_slash(char *s, char sep);

#endif
