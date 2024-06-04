/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:12:17 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/27 17:03:26 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_envp(char **env, t_pipex *p);
static char	*get_pathname(char **env, char *cmd, t_pipex *p, int ncmd);
static void	make_path(char *path, char *s1, char *s2);

int	parse(int ac, char **av, char **envp, t_pipex *p)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
	{
		ft_printf("%s", STR_ERR);
		exit(2);
	}
	if (open_files(av[1], av[ac - 1], p) != 0)
		exit(3);
	if (get_envp(envp, p) != 0)
	{
		close_files(p);
		ft_printf("%s", ENVP_ERR);
		exit(4);
	}
	init_var(p, av);
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

void	init_var(t_pipex *p, char **av)
{
	p->cmd_1 = malloc(sizeof(t_cmd));
	if (!p->cmd_1)
	{
		close_files(p);
		destroy_list(p);
		exit(5);
	}
	p->cmd_2 = malloc(sizeof(t_cmd));
	if (!p->cmd_2)
	{
		close_files(p);
		destroy_list(p);
		exit(6);
	}
	p->tube[0] = -1;
	p->tube[1] = -1;
	p->cmd_1->pid = -1;
	p->cmd_2->pid = -1;
	p->access1 = 0;
	p->access2 = 0;
	p->cmd_1->args = ft_split(av[2], ' ');
	p->cmd_1->pathname = get_pathname(p->env_path, p->cmd_1->args[0], p, 1);
	p->cmd_2->args = ft_split(av[3], ' ');
	p->cmd_2->pathname = get_pathname(p->env_path, p->cmd_2->args[0], p, 2);
}

/*	This function sets the filename as "/path/to/cmd"	*/
static char	*get_pathname(char **env, char *cmd, t_pipex *p, int ncmd)
{
	int		k;
	char	*path;

	k = 0;
	path = NULL;
	if (ft_char_in_str(cmd, '/') == 1)
		return (cmd);
	while (env[k])
	{
		path = malloc((ft_strlen(env[k]) + ft_strlen(cmd) + 1) * sizeof(char));
		if (path == NULL)
			continue ;
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

