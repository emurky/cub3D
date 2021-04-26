/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:27:54 by emurky            #+#    #+#             */
/*   Updated: 2021/04/26 23:34:14 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*clear;

	while (*lst)
	{
		clear = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(clear);
	}
	*lst = NULL;
}
