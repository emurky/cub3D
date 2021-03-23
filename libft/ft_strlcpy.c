/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:08:52 by emurky            #+#    #+#             */
/*   Updated: 2020/11/10 05:08:57 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t srclen;

	if (!src)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize)
	{
		while (*src && --dstsize)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (srclen);
}
