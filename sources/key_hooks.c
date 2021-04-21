/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:50:33 by emurky            #+#    #+#             */
/*   Updated: 2021/04/22 02:23:51 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	printf("Map was freed properly\n");
}

int		print_key(int key, t_all *all)
{
	(void)all;
	printf("%d was pressed\n", key);
	return (0);
}

int		close_window(t_all *all)
{
	(void)all;
	printf("Bye-bye\n");
	exit(0);
}

void	key_press(int key, t_all *all)
{
	if ((key == KEY_W || key == KEY_UP) && !wall_collision(all, 0))
		move_player(all, 0);
	if ((key == KEY_S || key == KEY_DOWN) && !wall_collision(all, M_PI))
		move_player(all, M_PI);
	if (key == KEY_A && !wall_collision(all, M_PI_2))
		move_player(all, M_PI_2);
	if (key == KEY_D && !wall_collision(all, -M_PI_2))
		move_player(all, -M_PI_2);
	if (key == KEY_LEFT)
		set_player_dir(all, all->plr.dir + ROTATE_SPEED);
	if (key == KEY_RIGHT)
		set_player_dir(all, all->plr.dir - ROTATE_SPEED);
	if (key == KEY_R)
	{
		set_player_pos(all, 27, 11);
		set_player_dir(all, M_PI_2);
	}
	if (key == KEY_ESC)
	{
		clean_map(all->map);
		exit(0);
	}
}
