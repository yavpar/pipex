/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:24:41 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/08 18:25:51 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	new_word = (char *)malloc((len_word + 1) * sizeof(char));
	if (!new_word)
		return (NULL);
	while (k < len_word)
	{
		new_word[k] = s[k];
		k++;
	}
	new_word[len_word] = '\0';
	return (new_word);
}

char	**ft_split(char *s, char sep)
{
	char	**word;
	int		k;
	int		n_words;

	n_words = count_words(s, sep);
	word = (char **)malloc(((n_words + 1) * sizeof(char *)));
	if (!word)
		return (NULL);
	word[n_words] = NULL;
	k = 0;
	while (*s && k < n_words)
	{
		if (*s != sep)
		{
			word[k++] = gen_word(s, sep);
			if (!word[k - 1])
				return (ft_free_array((void **)word, k - 1), NULL);
			while (*s && *s != sep)
				s++;
		}
		else
			s++;
	}
	return (word);
}
