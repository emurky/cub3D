/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:45:09 by emurky            #+#    #+#             */
/*   Updated: 2020/11/17 16:45:12 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list	*ret;

	if (!lst)
		return (NULL);
	while (lst)
	{
		ret = lst;
		lst = lst->next;
	}
	return (ret);
}
