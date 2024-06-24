/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:03:05 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/16 17:50:28 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FLAG_FDIN (O_RDONLY)
# define READ_END 0
# define WRITE_END 1
# define INPUT_ERR1 "Not enough arguments in the command line\n"
# define INPUT_ERR2 "Format: <infile> <cmd1> <cmd2> <outfile>\n"
# define INFILE_ERR "No such file or directory\n"
# define OUTFILE_ERR "File not opened\n"
# define FORK1_ERR "FORK: First fork not executed\n"
# define FORK2_ERR "FORK: Second fork not executed\n"
# define STR_ERR "pipex: There are one or several empty strings\n"
# define ENVP_ERR "ENVP: problem with malloc"
# define BUFERSIZE 1024

typedef struct s_cmd
{
	char	**args;
	char	*pathname;
	int		pid;
}			t_cmd;

typedef struct s_pipex
{
	int		fdin;
	int		fdout;
	int		tube[2];
	int		fd_err[2];
	char	**env_path;
	t_cmd	*cmd_1;
	t_cmd	*cmd_2;
	int		access1;
	int		access2;
	char	*arg1;
	char	*arg2;
	int		error_cmd1;
	int		error_cmd2;
}			t_pipex;

/*	FOR PARSING ARGUMENTS	*/
int			parse(int ac, char **av, char **envp, t_pipex *p);

/*	FOR HANDLING FILES	*/
void		open_files(char *in_file, char *out_file, t_pipex *pipex);
void		close_files(int n, ...);

/*	FOR EXECUTING BINARYS	*/
int			pipex(t_pipex *p);
int			wait_pids(t_pipex *p);

/*	UTILS	*/
void		destroy_list(t_pipex *p);
char		**split_add_slash(char *s, char sep);
void		print_err(char *err);
void		fatal_error(t_pipex *p, int err);
void		printf_fd(int fd, char *s1, char *s2);
int			read_and_print_errors(int fd_error);
int			len_cmds(char **cmd);

#endif
