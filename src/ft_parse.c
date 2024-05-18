/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:12:17 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/18 19:03:38 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_envp(char **env, t_pipex *p);
static char	*get_pathname(char **env_path, char *cmd);

int	parse(int ac, char **av, char **envp, t_pipex *p)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
	{
		ft_printf("%s", STR_ERR);
		exit(EXIT_FAILURE);
	}
	if (open_files(av[1], av[ac - 1], p) != 0)
		exit(EXIT_FAILURE);
	if (get_envp(envp, p) != 0)
	{
		close_files(p);
		ft_printf("ENVP_ERR");
		exit(EXIT_SUCCESS);
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

/*	This function defines "filename"	*/

static char	*get_pathname(char **env_path, char *cmd)
{
	int		k;
	char	*pathname;
	
	k = 0;
	pathname = NULL;
	if (ft_char_in_str(cmd, '/') == 1)
		return (cmd);
	while (env_path[k])
	{
		pathname = ft_strjoin(env_path[k], cmd);
		if (pathname == NULL)
			continue ;
		if (access(pathname, X_OK || F_OK) == 0)
			return (pathname);
		free(pathname);
		k++;
	}
	return (cmd);
}

void	init_var(t_pipex *p, char **av)
{
	p->cmd_1 = malloc(sizeof(t_cmd));
	if (!p->cmd_1)
	{
		close_files(p);
		destroy_list(p);
		exit (EXIT_FAILURE);
	}
	p->cmd_2 = malloc(sizeof(t_cmd));
	if (!p->cmd_2)
	{
		close_files(p);
		destroy_list(p);
		exit(EXIT_FAILURE);
	}
	p->tube[0] = -1;
	p->tube[1] = -1;
	p->cmd_1->pid = -1;
	p->cmd_2->pid = -1;
	p->cmd_1->args = ft_split(av[2], ' ');
	p->cmd_1->pathname = get_pathname(p->env_path, p->cmd_1->args[0]);
	p->cmd_2->args = ft_split(av[3], ' ');
	p->cmd_2->pathname = get_pathname(p->env_path, p->cmd_2->args[0]);
}
