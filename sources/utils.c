/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:40:54 by emurky            #+#    #+#             */
/*   Updated: 2021/04/23 12:28:12 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error()
{

}

void	malloc_with_check(void **ptr, size_t size)
{
	*ptr = NULL;
	*ptr = malloc(size);
	if (!(*ptr))
		error();
}

int		is_player_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_pos(t_all *all, int x, int y)
{
	all->plr.x = x * SCALE + MAP_OFFS_X + SCALE / 2.0;
	all->plr.y = y * SCALE + MAP_OFFS_Y + SCALE / 2.0;
	all->ray.pos_x = x + 1.0 / 2.0;
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
	// return (all->map
	// 	[(int)(all->ray.pos_y - sin(all->plr.dir + angle) / 1)]
	// 	[(int)(all->ray.pos_x + cos(all->plr.dir + angle) / 1)]
	// 	== '1');
	return (all->map
		[scaled_down_y(all->plr.y - sin(all->plr.dir + angle) * (MOVE_SPEED * 1))]
		[scaled_down_x(all->plr.x + cos(all->plr.dir + angle) * (MOVE_SPEED * 1))]
		== '1');
}
