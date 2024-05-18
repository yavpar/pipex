#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define FLAG_FDIN (O_RDONLY)
# define FLAG_FDOUT (O_CREAT | O_WRONLY | O_TRUNC)
# define READ_END 0
# define WRITE_END 1
# define INPUT_ERR1 "Not enough arguments in the command line\n"
# define INPUT_ERR2 "Format: <infile> <cmd1> <cmd2> <outfile>\n"
# define INFILE_ERR "FD: Infile not opened\n"
# define OUTFILE_ERR "FD: Outfile not opened\n"
# define PIPE_ERR "PIPE: Pipe not executed\n"
# define FORK1_ERR "FORK: First fork not executed\n"
# define FORK2_ERR "FORK: Second fork not executed\n"
# define STR_ERR "There are one or several empty strings\n"
# define ENVP_ERR "ENVP: problem with malloc"

typedef struct s_cmd
{
	char	**args;
	char	*pathname;
	int		pid;
}			t_cmd;

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		tube[2];
	char	**env_path;
	t_cmd	*cmd_1;
	t_cmd	*cmd_2;
}			t_pipex;

/*	FOR PARSING ARGUMENTS	*/
int		parse(int ac, char **av, char **envp, t_pipex *p);

/*	FOR HANDLING FILES	*/
int		open_files(char *in_file, char *out_file, t_pipex *pipex);
void	close_files(t_pipex *p);

/*	FOR EXECUTING BINARYS	*/
int		pipex(t_pipex *p);
void	wait_pids(t_pipex *p);

/*	UTILS	*/
void	destroy_list(t_pipex *p);
char	**split_add_slash(char *s, char sep);
void	init_var(t_pipex *p, char **av);

#endif
