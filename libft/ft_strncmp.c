/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:54:01 by emurky            #+#    #+#             */
/*   Updated: 2021/04/05 22:46:50 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (*s1 == *s2 && *s1 && --n)
		{
			s1++;
			s2++;
		}
		return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
	}
	return (0);
}
