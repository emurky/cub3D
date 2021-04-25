/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:03:08 by emurky            #+#    #+#             */
/*   Updated: 2021/04/25 23:11:48 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t		counter;

	counter = 0;
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

static char	**ft_free_splitted(char **splitted)
{
	while (*splitted)
		free(*splitted++);
	free(splitted);
	return (NULL);
}

static int	malloc_splitted(char ***splitted, size_t words_count, size_t *i)
{
	*i = 0;
	*splitted = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!(*splitted))
		return (0);
	(*splitted)[words_count] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t		words_count;
	size_t		word_len;
	size_t		i;
	char		**splitted;

	if (!s)
		return (NULL);
	words_count = ft_count_words(s, c);
	if (!malloc_splitted(&splitted, words_count, &i))
		return (NULL);
	while (*s && i < words_count)
	{
		word_len = 0;
		while (*s && *s == c)
			s++;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		splitted[i] = ft_substr(s, 0, word_len);
		if (!splitted[i])
			return (ft_free_splitted(splitted));
		if (*s)
			s += word_len;
		i++;
	}
	return (splitted);
}
