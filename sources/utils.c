/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:40:54 by emurky            #+#    #+#             */
/*   Updated: 2021/04/21 18:36:48 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->linelen + x * (img->bpp / 8));
	return (*(unsigned int*)pixel);
}

int		is_player_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_pos(t_all *all, int x, int y)
{
	all->plr.x = x * SCALE + MAP_OFFS_X - SCALE / 2.0;
	all->plr.y = y * SCALE + MAP_OFFS_Y + SCALE / 2.0;
	all->ray.pos_x = x - 1.0 / 2.0;
	all->ray.pos_y = y + 1.0 / 2.0;
}

void	set_player_dir(t_all *all, double dir)
{
	all->plr.dir = dir;
	all->plr.start = dir - FOV / 2;
	all->plr.end = dir + FOV / 2;
}

void	move_player(t_all *all, double dir)
{
	all->plr.x += cos(all->plr.dir + dir) * MOVE_SPEED;
	all->plr.y -= sin(all->plr.dir + dir) * MOVE_SPEED;
	// printf("%f posx %f posy map\n", all->plr.x, all->plr.y);
	all->ray.pos_x += cos(all->plr.dir + dir) * MOVE_SPEED / SCALE;
	all->ray.pos_y -= sin(all->plr.dir + dir) * MOVE_SPEED / SCALE;
	// printf("%f posx %f posy ray\n", all->ray.pos_x, all->ray.pos_y);
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

int		wall_collision(t_all *all, double angle)
{
	return (all->map
		[scaled_down_y(all->plr.y - sin(all->plr.dir + angle) * MOVE_SPEED)]
		[scaled_down_x(all->plr.x + cos(all->plr.dir + angle) * MOVE_SPEED)]
		== '1');
}
