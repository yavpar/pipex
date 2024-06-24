/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:12:17 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/16 17:47:58 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_envp(char **env, t_pipex *p);
static char	*get_pathname(char **env, char *cmd, t_pipex *p, int ncmd);
static void	make_path(char *path, char *s1, char *s2);
static void	set_var(t_pipex *p, char **av);

int	parse(int ac, char **av, char **envp, t_pipex *p)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
	{
		ft_printf("%s%s", STR_ERR, INPUT_ERR2);
		exit(1);
	}
	if (av[1][0] == '\0' && av[2][0] == '\0' && av[3][0] == '\0'
		&& av[4][0] == '\0')
	{
		ft_printf("%s%s", STR_ERR, INPUT_ERR2);
		exit(1);
	}
	open_files(av[1], av[ac - 1], p);
	if (get_envp(envp, p) != 0)
	{
		ft_printf("%s", ENVP_ERR);
		close_files(2, p->fdin, p->fdout);
		exit(1);
	}
	set_var(p, av);
	return (0);
}

static int	get_envp(char **env, t_pipex *p)
{
	char	*path;
	int		k;

	k = 0;
	p->env_path = NULL;
	path = NULL;
	while (env[k])
	{
		if (ft_strncmp(env[k], "PATH=", 5) == 0)
		{
			path = env[k];
			path = &path[5];
			break ;
		}
		k++;
	}
	p->env_path = split_add_slash(path, ':');
	if (p->env_path == NULL)
		return (1);
	return (0);
}

static void	set_var(t_pipex *p, char **av)
{
	p->cmd_1 = ft_calloc(1, sizeof(t_cmd));
	if (!p->cmd_1)
		fatal_error(p, 1);
	p->cmd_2 = ft_calloc(1, sizeof(t_cmd));
	if (!p->cmd_2)
		fatal_error(p, 1);
	if (av[2][0] == '\0')
		p->error_cmd1 = 1;
	if (av[3][0] == '\0')
		p->error_cmd2 = 1;
	p->cmd_1->args = ft_split(av[2], ' ');
	if (av[2][0] == '\0')
		p->cmd_1->pathname = NULL;
	else
		p->cmd_1->pathname = get_pathname(p->env_path, p->cmd_1->args[0], p, 1);
	p->cmd_2->args = ft_split(av[3], ' ');
	if (av[3][0] == '\0')
		p->cmd_2->pathname = NULL;
	else
		p->cmd_2->pathname = get_pathname(p->env_path, p->cmd_2->args[0], p, 2);
}

/*	This function sets the filename as "/path/to/cmd"	*/
static char	*get_pathname(char **env, char *cmd, t_pipex *p, int ncmd)
{
	int		k;
	char	*path;

	k = 0;
	if (ft_char_in_str(cmd, '/') == 1)
		return (cmd);
	while (cmd && env[k])
	{
		path = ft_calloc((ft_strlen(env[k]) + ft_strlen(cmd) + 1),
				sizeof(char));
		if (path == NULL)
			fatal_error(p, 1);
		make_path(path, env[k], cmd);
		if (access(path, X_OK) == 0)
		{
			if (ncmd == 1)
				p->access1 = 1;
			else
				p->access2 = 1;
			return (path);
		}
		k++;
		free(path);
	}
	return (cmd);
}

/*	This function concatenate the path and the binary command	*/
/*	as "/path/to/cmd"											*/
static void	make_path(char *path, char *s1, char *s2)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (s1[k])
	{
		path[j] = s1[k];
		j++;
		k++;
	}
	k = 0;
	while (s2[k])
	{
		path[j] = s2[k];
		j++;
		k++;
	}
	path[j] = '\0';
}
