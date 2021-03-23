/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:54:18 by emurky            #+#    #+#             */
/*   Updated: 2020/11/09 04:54:20 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dstptr;
	const unsigned char	*srcptr;

	if (!dst && !src)
		return (0);
	dstptr = dst;
	srcptr = src;
	while (n-- && *srcptr != (unsigned char)c)
		*dstptr++ = *srcptr++;
	if (*srcptr == (unsigned char)c)
	{
		*dstptr = *srcptr;
		return (++dstptr);
	}
	else
		return (0);
}
