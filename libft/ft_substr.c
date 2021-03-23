/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:28:18 by emurky            #+#    #+#             */
/*   Updated: 2020/11/16 00:28:22 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	string_length;

	if (!s)
		return (NULL);
	string_length = ft_strlen(s);
	if (start >= string_length)
		return (ft_strdup(""));
	if (len > string_length - start)
	{
		if (!(sub = malloc(sizeof(char) * (string_length - start + 1))))
			return (NULL);
	}
	else if (len <= string_length - start)
	{
		if (!(sub = malloc(sizeof(char) * (len + 1))))
			return (NULL);
	}
	i = 0;
	while (s[start] && len--)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
