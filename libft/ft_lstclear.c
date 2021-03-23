/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:27:54 by emurky            #+#    #+#             */
/*   Updated: 2020/11/17 18:27:56 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clear;

	while (*lst)
	{
		clear = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(clear, del);
	}
	*lst = NULL;
}
