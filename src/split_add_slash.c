/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_add_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:40:01 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/11 14:47:53 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char *s, char separator);
static char	*gen_word(char *s, char separator);

char	**split_add_slash(char *s, char sep)
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

