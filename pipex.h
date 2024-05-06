
#ifndef	PIPEX_H
#define	PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define FLAG_FDIN (O_RDONLY)
#define FLAG_FDOUT (O_CREAT | O_WRONLY | O_TRUNC)

typedef struct	s_pipex
{
	char		*fd_infile;
	char		*fd_outfile;
	char		**env_path;
	char		**cmds_tab;
	int			cmds;
}				t_pipex;

typedef struct	s_cmd
{
	char		**args;
	char		*filename;
	int			fd[2];
	int			pid;
}				t_cmd;

void	ft_parse(int ac, char **av, char **env);
int	get_envp(char **env, t_pipex *pipex);
int	ft_open_files(char *in_file, char *out_file);


#endif
