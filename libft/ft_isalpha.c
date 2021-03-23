/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:56 by emurky            #+#    #+#             */
/*   Updated: 2020/11/03 23:16:00 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}