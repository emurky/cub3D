/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:28:18 by emurky            #+#    #+#             */
/*   Updated: 2021/04/05 23:25:28 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	substr_length_malloc(char **sub, unsigned int strlen,
								unsigned int start, size_t len)
{
	if (len > strlen - start)
	{
		*sub = malloc(sizeof(char) * (strlen - start + 1));
		if (!(*sub))
			return (0);
	}
	else if (len <= strlen - start)
	{
		*sub = malloc(sizeof(char) * (len + 1));
		if (!(*sub))
			return (0);
	}
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if (!substr_length_malloc(&sub, strlen, start, len))
		return (NULL);
	i = 0;
	while (s[start] && len--)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
