/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:40:54 by emurky            #+#    #+#             */
/*   Updated: 2021/04/24 23:52:39 by emurky           ###   ########.fr       */
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
	all->ray.pos_x = x + 0.5;
	all->ray.pos_y = y + 0.5;
}

void	set_player_dir(t_all *all, double dir)
{
	all->plr.dir = dir;
	all->plr.start = dir - FOV / 2;
	all->plr.end = dir + FOV / 2;
}

int		wall_collision_y(t_all *all, double dir)
{
	return (all->map
		[(int)(all->ray.pos_y - sin(all->plr.dir + dir) * MOVE_SPEED * 1.1)]
		[(int)(all->ray.pos_x)]
		== '1');
}

int		wall_collision_x(t_all *all, double dir)
{
	return (all->map
		[(int)(all->ray.pos_y)]
		[(int)(all->ray.pos_x + cos(all->plr.dir + dir) * MOVE_SPEED * 1.1)]
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

// int		wall_collision(t_all *all, double angle)
// {
// 	return (all->map
// 		[(int)(all->ray.pos_y - sin(all->plr.dir + angle) / 1)]
// 		[(int)(all->ray.pos_x + cos(all->plr.dir + angle) / 1)]
// 		== '1');
// 	// return (all->map
// 	// 	[scaled_down_y(all->plr.y - sin(all->plr.dir + angle) * (MOVE_SPEED * 1))]
// 	// 	[scaled_down_x(all->plr.x + cos(all->plr.dir + angle) * (MOVE_SPEED * 1))]
// 	// 	== '1');
// }

// int		sprite_collision_y(t_all *all, double dir)
// {
// 	for (int i = 0; i < all->ray.num_sprs; i++)
// 		printf("%5.1f posx %5.1f posy %2d order %7.2f dist #%2d sprite\n",
// 		all->ray.sprites[i].x, all->ray.sprites[i].y, all->ray.sprites[i].order, all->ray.sprites[i].dist, i + 1);

// 	// if (all->ray.sprites[all->ray.num_sprs - 1].y - 0.1 <= all->ray.pos_y - sin(all->plr.dir + dir) * MOVE_SPEED 
// 	// && all->ray.pos_y - sin(all->plr.dir + dir) * MOVE_SPEED <= all->ray.sprites[all->ray.num_sprs - 1].y + 0.1)
// 	// 	return (1);
// 	// (void)dir;
// 	if (sin(all->ray.sprites[all->ray.num_sprs - 1].dist) + sin(all->plr.dir + dir) <= 0.05)
// 		return (1);
// 	else
// 	//  (void)all;
// 		return (0);
// 	// return (all->map
// 	// 	[(int)(all->ray.pos_y - sin(all->plr.dir + dir) * MOVE_SPEED * 0.5)]
// 	// 	[(int)(all->ray.pos_x)]
// 	// 	== '2');
// }

// int		sprite_collision_x(t_all *all, double dir)
// {
// 	(void)dir;
// 	if (all->ray.sprites[all->ray.num_sprs - 1].dist + cos(all->plr.dir + dir) <= 0.05)
// 		return (1);
// 	else
// 	//  (void)all;
// 		return (0);


// 	// if (all->ray.sprites[all->ray.num_sprs - 1].x - 0.1 <= all->ray.pos_x + cos(all->plr.dir + dir) * MOVE_SPEED 
// 	// && all->ray.pos_x + cos(all->plr.dir + dir) * MOVE_SPEED <= all->ray.sprites[all->ray.num_sprs - 1].x + 0.1)
// 	// 	return (1);
// 	// else
// 	// // (void)dir; (void)all;
// 	// 	return (0);
// 	// return (all->map
// 	// 	[(int)(all->ray.pos_y)]
// 	// 	[(int)(all->ray.pos_x + cos(all->plr.dir + dir) * MOVE_SPEED * 0.5)]
// 	// 	== '2');
// }


// void	move_player(t_all *all, double dir)
// {
// 	all->plr.x += cos(all->plr.dir + dir) * MOVE_SPEED;
// 	all->plr.y -= sin(all->plr.dir + dir) * MOVE_SPEED;
// 	// printf("%f posx %f posy map\n", all->plr.x, all->plr.y);
// 	all->ray.pos_x += cos(all->plr.dir + dir) * MOVE_SPEED / SCALE;
// 	all->ray.pos_y -= sin(all->plr.dir + dir) * MOVE_SPEED / SCALE;
// 	// printf("%f posx %f posy ray\n", all->ray.pos_x, all->ray.pos_y);
// }
