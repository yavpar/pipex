
#include "pipex.h"

static int	get_envp(char **env, t_pipex *pipex);
static int	get_cmd();

int	parse(int ac, char **av, char **envp, t_pipex *pipex)
{
	int	k;

	k = 0;
	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		exit (2);
	if (ft_open_files((av[1], av[4]), pipex))
	{
		free(pipex);
		exit(3);
	}
	if (get_envp(envp, pipex))
	{
		free(pipex);
		exit (4)
	}
	if (get_cmd(ac, av + 2, pipex))
	{
		ft_close_files();
		ft_free_array(pipex->env_path);
		free (pipex);
		exit(5);
	}
	return (0);
}

static int	get_envp(char **env, t_pipex *pipex)
{
	char *path;
	int	k;
	
	k = 0;
	pipex->env_path = NULL;
	path = NULL;
	while (env[k])
	{
		if (ft_strncmp(env[k], "PATH=", 5) == 0)
		{
			path = env[k];
			path = path + 5;
			break ;
		}
		k++;
	}
	pipex->env_path = ft_split(path, ':');
	if (pipex->env_path == NULL)
	{
		printf("ERROR: split environement\n");
		return (4);
	}
	return (0);
}

/*	This function creates an array of pointers, each pointer points	*/
/*	to another array of pointers who contains the variables to use	*/
/*	for EXECVE funtion. 											*/

int	get_cmd(int ac, char **av, t_pipex *pipex)
{
	int	k;
	int	cmd;
	t_cmd	*cmd_lst;

	cmd_lst = NULL;
	k = 1;
	cmd = 0;
	pipex->cmds = ac - 3;
	pipex->cmds_tab = (void **)malloc((sizeof(int *) * pipex->cmds) + 1);
	if (pipex->cmds_tab == NULL)
		return (1);
	while (k <= pipex->cmds)
	{
		k++;
		cmd_lst = (t_cmd *)malloc(sizeof(t_cmd));
		if (cmd_lst == NULL)
		{
			distroy_list(pipex, cmd_lst);// crear funcion para liberar memoria de el array y las estructuras;
			exit (1);
		}
		pipex->cmds_tab[cmd++] = cmd_lst;
		cmd_lst->args = ft_split(av[k], ' ');
		if (cmd_lst->args == NULL)
		{
			distroy_list(pipex, cmd_lst); // y el las estructuras
			return (1);
		}
		if (ft_strnstr(cmd_lst->args, "/") == 0)
			set_cmd_path(pipex, cmd_lst);
		else
			set_cmd_env(pipex, cmd_lst);
	}
	return (0);
}
// a mejorar con la nueva estructura




int	set_cmd_path(t_pipex *pipex, t_cmd *cmd_lst)
{

}

int set_cmd_env(t_pipex *pipex, t_cmd *cmd_lst)
{
	int	k;
	char *cmd;

	k = 0;
	while (pipex->env_path[k])
	{
		cmd = ft_strjoin(pipex->env_path[k], cmd_lst->args);
		if (cmd == NULL)
		{
			distroy_list(pipex, cmd_lst);
			return (1);
		}
		if 	(acces(cmd, X_OK) == 0)
		{
			cmd_lst->filename = cmd; /* si tengo acceso, apunto a la nueva direccion*/
			free(cmd_lst->args[0]); /* libero la memoria del nombre del comando*/
			cmd_lst->args[0] = cmd; /* asigno el nuevo comando con el path adecuado */
			break ; /* salgo de la bucle */
		}
		free(cmd);
		k++;
	}
}

//
//
//

/*	This function frees a array pointers	*/
void	ft_free_array(void **s, int size_s, void(ft_free)(void *))
{
	int	k;

	k = 0;
	if (s)
	{
		while (k < size_s)
		{
			ft_free(s[k]);
			k++;
		}
		ft_free(s);
	}
}

void	ft_free(void *data)
{
	if (data)
		free(data);
}

static int	count_words(char *s, char separator)
{
	int	k;

	k = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == separator)
		{
			s++;
		}
		else
		{
			k++;
			while (*s && *s != separator)
				s++;
		}
	}
	return (k);
}

static char	*gen_word(char *s, char separator)
{
	char	*new_word;
	int		len_word;
	int		k;

	if (!s || separator == '\0')
		return (NULL);
	len_word = 0;
	k = 0;
	while (s[len_word] && s[len_word] != separator)
		len_word++;
	new_word = (char *)malloc((len_word + 2) * sizeof(char));
	if (!new_word)
		return (NULL);
	new_word[len_word] = '\0';
	while (k < len_word)
	{
		new_word[k] = s[k];
		k++;
	}
	new_word[k] = '/';
	return (new_word);
}

char	**ft_split(char *s, char sep)
{
	char	**list_words;
	int		k;
	int		n_words;

	n_words = count_words(s, sep);
	list_words = (char **)malloc(((n_words + 1) * sizeof(char *)));
	if (!list_words)
		return (NULL);
	list_words[n_words] = NULL;
	k = 0;
	while (*s && k < n_words)
	{
		if (*s != sep)
		{
			list_words[k++] = gen_word(s, sep);
			if (!list_words[k - 1])
				return (ft_free_array((void **)list_words, k - 1,
						(void (*)(void *))ft_free), NULL);
			while (*s && *s != sep)
				s++;
		}
		else
			s++;
	}
	return (list_words);
}

//
//
//

char	*ft_strdup(const char *s)
{
	int		i;
	int		l;
	char	*cpy;

	l = ft_strlen(s);
	if (!s)
		return (NULL);
	i = 0;
	cpy = (char *)malloc(sizeof(char) * l + 1);
	if (!cpy)
		return (NULL);
	while (i < l)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
/* Returns a new string copied from s*/

//
//
//


size_t	ft_strlen(const char *s)
{
	size_t	k;

	k = 0;
	while (s[k])
		k++;
	return (k);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		l;
	char	*cpy;

	l = ft_strlen(s);
	if (!s)
		return (NULL);
	i = 0;
	cpy = (char *)malloc(sizeof(char) * l + 1);
	if (!cpy)
		return (NULL);
	while (i < l)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoind;
	size_t	k;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && *s2)
		return (ft_strdup(s2));
	if (*s1 && !s2)
		return (ft_strdup(s1));
	strjoind = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!strjoind)
		return (NULL);
	k = 0;
	while (*s1)
		*(strjoind + k++) = *s1++;
	while (*s2)
		*(strjoind + k++) = *s2++;
	*(strjoind + k) = '\0';
	return (strjoind);
}

//
//
//

size_t	ft_strlen(const char *s)
{
	size_t	k;

	k = 0;
	while (s[k])
		k++;
	return (k);
}
