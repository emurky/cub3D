/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:12:00 by emurky            #+#    #+#             */
/*   Updated: 2021/04/05 22:47:45 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fstr;
	unsigned int	i;

	if (!s)
		return (NULL);
	fstr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!fstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		fstr[i] = (*f)(i, s[i]);
		i++;
	}
	fstr[i] = '\0';
	return (fstr);
}
