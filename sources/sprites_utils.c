/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:09:30 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 03:10:24 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	swap_sprites(t_spr *a, t_spr *b)
{
	t_spr	c;

	c = *b;
	*b = *a;
	*a = c;
}

void	sprites_counting(t_all *all)
{
	int		i;
	int		j;

	all->ray.num_sprs = 0;
	j = 0;
	while (all->map[j])
	{
		i = 0;
		while (all->map[j][i])
		{
			if (all->map[j][i] == '2')
				all->ray.num_sprs++;
			i++;
		}
		j++;
	}
}

void	quicksort_sprites(t_spr *sprites, int first, int last)
{
	int		i;
	int		j;
	int		pivot;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (sprites[i].dist >= sprites[pivot].dist && i < last)
				i++;
			while (sprites[j].dist < sprites[pivot].dist)
				j--;
			if (i < j)
				swap_sprites(&sprites[j], &sprites[i]);
		}
		swap_sprites(&sprites[j], &sprites[pivot]);
		quicksort_sprites(sprites, first, j - 1);
		quicksort_sprites(sprites, j + 1, last);
	}
}
