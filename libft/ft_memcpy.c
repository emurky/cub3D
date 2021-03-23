/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:16:24 by emurky            #+#    #+#             */
/*   Updated: 2020/11/09 04:16:26 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dstptr;
	const unsigned char	*srcptr;

	if (!dst && !src)
		return (NULL);
	dstptr = dst;
	srcptr = src;
	while (n--)
		*dstptr++ = *srcptr++;
	return (dst);
}
