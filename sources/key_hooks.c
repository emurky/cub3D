/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:50:33 by emurky            #+#    #+#             */
/*   Updated: 2021/04/23 13:49:34 by emurky           ###   ########.fr       */
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
	map = NULL;
	printf("map was freed\n");
}

void	free_malloc_pointers(t_all *all)
{
	if (all->ray.z_buff)
		free(all->ray.z_buff);
	if (all->ray.sprites)
		free(all->ray.sprites);
	printf("malloced pointers were freed\n");
}

void	clean_mlx(t_all *all)
{
	int		i;

	i = 0;
	if (all->mlx && all->win)
		mlx_destroy_window(all->mlx, all->win);
	if (all->mlx && all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	while (i < 5)
	{
		if (all->mlx && all->tex[i].img)
			mlx_destroy_image(all->mlx, all->tex[i].img);
		i++;
	}
	printf("mlx was freed\n");
}

int		print_key(int key, t_all *all)
{
	(void)all;
	printf("%d was pressed\n", key);
	return (0);
}

int		close_window(t_all *all)
{
	clean_map(all->map);
	clean_mlx(all);
	free_malloc_pointers(all);
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
		set_player_pos(all, 26, 11);
		set_player_dir(all, M_PI_2);
	}
	if (key == KEY_ESC)
	{
		clean_mlx(all);
		clean_map(all->map);
		free_malloc_pointers(all);
		exit(0);
	}
}
