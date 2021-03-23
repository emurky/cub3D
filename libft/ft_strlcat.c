/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:09:08 by emurky            #+#    #+#             */
/*   Updated: 2020/11/10 05:09:10 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		dstlen;
	size_t		len;

	d = dst;
	s = src;
	len = dstsize;
	while (*d && len--)
		d++;
	dstlen = d - dst;
	len = dstsize - dstlen;
	if (!len)
		return (dstlen + ft_strlen(src));
	while (*s)
	{
		if (len != 1)
		{
			*d++ = *s;
			len--;
		}
		s++;
	}
	*d = '\0';
	return (dstlen + s - src);
}
