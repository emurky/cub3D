/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:40:54 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 07:53:05 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	is_player_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	scale_x(double index)
{
	return ((index - MAP_OFFS_X) / SCALE);
}

int	scale_y(double index)
{
	return ((index - MAP_OFFS_Y) / SCALE);
}

void	is_enough_space_for_map(t_all *all)
{
	t_pnt	max;

	max.x = 0;
	max.y = 0;
	max.x = all->max_map.x * SCALE + MAP_OFFS_X * 2;
	max.y = all->max_map.y * SCALE + MAP_OFFS_Y * 2;
	if (max.x < all->screen.x && max.y < all->screen.y && DRAW_MAP)
		all->flags[ISMAP_OK] = TRUE;
}
