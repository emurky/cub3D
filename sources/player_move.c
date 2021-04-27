/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 04:39:56 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 00:16:53 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_pos(t_all *all, int x, int y)
{
	all->plr.x = x * SCALE + MAP_OFFS_X + SCALE / 2.0;
	all->plr.y = y * SCALE + MAP_OFFS_Y + SCALE / 2.0;
	all->ray.pos_x = x + 0.5;
	all->ray.pos_y = y + 0.5;
}

void	set_player_dir(t_all *all, double dir)
{
	all->plr.dir = dir;
	all->plr.start = dir - FOV / 2;
	all->plr.end = dir + FOV / 2;
}

int	wall_collision_y(t_all *all, double dir)
{
	return (all->map
		[(int)(all->ray.pos_y - sin(all->plr.dir + dir) * MOVE_SPEED * 7.0)]
		[(int)(all->ray.pos_x)]
		== '1');
}

int	wall_collision_x(t_all *all, double dir)
{
	return (all->map
		[(int)(all->ray.pos_y)]
		[(int)(all->ray.pos_x + cos(all->plr.dir + dir) * MOVE_SPEED * 7.0)]
		== '1');
}

void	move_player(t_all *all, double dir)
{
	if (!wall_collision_x(all, dir))
	{
		all->plr.x += cos(all->plr.dir + dir) * MOVE_SPEED * SCALE;
		all->ray.pos_x += cos(all->plr.dir + dir) * MOVE_SPEED;
	}
	if (!wall_collision_y(all, dir))
	{
		all->plr.y -= sin(all->plr.dir + dir) * MOVE_SPEED * SCALE;
		all->ray.pos_y -= sin(all->plr.dir + dir) * MOVE_SPEED;
	}
}

int	scale_x(double index)
{
	return ((index - MAP_OFFS_X) / SCALE);
}

int	scale_y(double index)
{
	return ((index - MAP_OFFS_Y) / SCALE);
}
