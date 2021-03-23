/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 01:44:35 by emurky            #+#    #+#             */
/*   Updated: 2020/11/14 01:44:38 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *s2;
	char *strdup;

	if (!(s2 = malloc(ft_strlen(s1) * sizeof(char) + 1)))
		return (NULL);
	strdup = s2;
	while (*s1)
		*s2++ = *s1++;
	*s2 = '\0';
	return (strdup);
}
