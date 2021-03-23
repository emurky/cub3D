/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 03:38:04 by emurky            #+#    #+#             */
/*   Updated: 2020/11/17 03:38:06 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*newnode;

	if (!(newnode = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}
