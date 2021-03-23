/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:35:12 by emurky            #+#    #+#             */
/*   Updated: 2020/11/16 21:35:13 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_static_charin(char c, const char *str)
{
	int		i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(str) + 1;
	while (slen--)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char		*trimmed;
	char		*trptr;
	const char	*end;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_static_charin(*s1, set) >= 0)
		s1++;
	end = s1;
	while (*end)
		end++;
	if (!(end - s1))
		return (ft_strdup(""));
	while (ft_static_charin(*end, set) >= 0)
		end--;
	if (!(trimmed = malloc(sizeof(char) * (++end - s1 + 1))))
		return (NULL);
	trptr = trimmed;
	while (s1 != end)
		*trptr++ = *s1++;
	*trptr = '\0';
	return (trimmed);
}
