/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:40:54 by emurky            #+#    #+#             */
/*   Updated: 2021/04/13 15:47:08 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		is_player_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_dir(t_plr *plr, double dir)
{
	plr->dir = dir;
	plr->start = dir - FOV / 2;
	plr->end = dir + FOV / 2;
}

int		scaled_down_x(double index)
{
	return ((index - MAP_OFFS_X) / SCALE);
}

int		scaled_down_y(double index)
{
	return ((index - MAP_OFFS_Y) / SCALE);
}

char	map_char(t_all *all)
{
	return (all->map[scaled_down_y(all->plr.y)][scaled_down_x(all->plr.x)]);
}
