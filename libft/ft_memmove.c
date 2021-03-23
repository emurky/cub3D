/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:45:57 by emurky            #+#    #+#             */
/*   Updated: 2020/11/09 23:45:59 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dstptr;
	const char	*srcptr;

	dstptr = dst;
	srcptr = src;
	if (dstptr == srcptr)
		return (dst);
	else if (dstptr < srcptr)
		while (len--)
			*dstptr++ = *srcptr++;
	else
	{
		dstptr += len;
		srcptr += len;
		while (len--)
			*(--dstptr) = *(--srcptr);
	}
	return (dst);
}
