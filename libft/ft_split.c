/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:03:08 by emurky            #+#    #+#             */
/*   Updated: 2020/11/18 02:03:10 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c, size_t *i)
{
	size_t		counter;

	counter = 0;
	*i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			counter++;
			while (*s && *s != c)
				s++;
		}
	}
	return (counter);
}

static char		**ft_free_splitted(char **splitted)
{
	while (*splitted)
		free(*splitted++);
	free(splitted);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	size_t		words_count;
	size_t		word_len;
	size_t		i;
	char		**splitted;

	if (!s)
		return (NULL);
	words_count = ft_count_words(s, c, &i);
	if (!(splitted = (char **)malloc(sizeof(char *) * (words_count + 1))))
		return (NULL);
	splitted[words_count] = NULL;
	while (*s && i < words_count)
	{
		word_len = 0;
		while (*s && *s == c)
			s++;
		while (*s && s[word_len] != c)
			word_len++;
		if (!(splitted[i] = ft_substr(s, 0, word_len)))
			return (ft_free_splitted(splitted));
		if (*s)
			s += word_len;
		i++;
	}
	return (splitted);
}
