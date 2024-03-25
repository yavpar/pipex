
#ifndef	PIPEX_H
#define	PIPEX_H

#include <errno.h>
#include <stdio.h>

typedef struct	s_pipex
{
	char		*fd_infile;
	char		*fd_outfile;
	char		**env_path;
	t_list		*cmd_list;
}				t_pipex;

typedef struct	s_cmd
{
	char		*filename;
	char		*args[];
	int			fd[2];
}				t_cmd;

void	ft_parse(int ac, char **av, char **env);

#endif
