/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:50:33 by emurky            #+#    #+#             */
/*   Updated: 2021/04/19 21:38:52 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		print_key(int key, t_all *all)
{
	(void)all;
	printf("%d was pressed\n", key);
	return (0);
}

int		esc_exit(int key, t_all *all)
{
	(void)all;
	// mlx_destroy_window(all->mlx, all->win);
	if (key == KEY_ESC)
	{
		// clean_map(&all->map);
		exit(0);
	}
	return (0);
}

int		close_window(t_all *all)
{
	(void)all;
	printf("Bye-bye\n");
	exit(0);
	// return (0);
}

void	key_press(int key, t_all *all)
{
	// if (map_char(all) == '1')
	// {
	// 	// printf("%f is x %f is y\n", all->plr.x, all->plr.y);
	// 	all->plr.dir += M_PI - 2 * all->plr.dir;
	// 	all->plr.start = all->plr.dir - FOV / 2;
	// 	all->plr.end = all->plr.dir + FOV / 2;
	// 	all->plr.x += cos(all->plr.dir) * SCALE / 4;
	// 	all->plr.y -= sin(all->plr.dir) * SCALE / 4;
	// }
	if ((key == KEY_W || key == KEY_UP) && !wall_collision(all, 0))
		move_player(&all->plr, 0);
	if ((key == KEY_S || key == KEY_DOWN) && !wall_collision(all, M_PI))
		move_player(&all->plr, M_PI);
	if (key == KEY_A && !wall_collision(all, M_PI_2))
		move_player(&all->plr, M_PI_2);
	if (key == KEY_D && !wall_collision(all, -M_PI_2))
		move_player(&all->plr, -M_PI_2);
	if (key == KEY_LEFT)
		set_player_dir(&all->plr, all->plr.dir + ROTATE_SPEED);
	if (key == KEY_RIGHT)
		set_player_dir(&all->plr, all->plr.dir - ROTATE_SPEED);
	if (key == KEY_R)
	{
		all->plr.x = 27.0 * SCALE + MAP_OFFS_X - SCALE / 2;
		all->plr.y = 11.0 * SCALE + MAP_OFFS_Y + SCALE / 2;
		set_player_dir(&all->plr, M_PI_2);
	}
	if (key == KEY_ESC)
	{
		// clean_map(all->map);
		exit(0);
	}
}
