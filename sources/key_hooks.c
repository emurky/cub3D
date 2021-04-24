/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:50:33 by emurky            #+#    #+#             */
/*   Updated: 2021/04/24 23:54:01 by emurky           ###   ########.fr       */
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

int		key_pressed(int key, t_all *all)
{
	if (key == KEY_W || key == KEY_UP)
		all->keys[0] = TRUE;
	else if (key == KEY_S || key == KEY_DOWN)
		all->keys[1] = TRUE;
	else if (key == KEY_A)
		all->keys[2] = TRUE;
	else if (key == KEY_D)
		all->keys[3] = TRUE;
	else if (key == KEY_LEFT)
		all->keys[4] = TRUE;
	else if (key == KEY_RIGHT)
		all->keys[5] = TRUE;
	else if (key == KEY_R)
		all->keys[6] = TRUE;
	else if (key == KEY_ESC)
		all->keys[7] = TRUE;
	return (0);
}

int		key_released(int key, t_all *all)
{
	if (key == KEY_W || key == KEY_UP)
		all->keys[0] = FALSE;
	else if (key == KEY_S || key == KEY_DOWN)
		all->keys[1] = FALSE;
	else if (key == KEY_A)
		all->keys[2] = FALSE;
	else if (key == KEY_D)
		all->keys[3] = FALSE;
	else if (key == KEY_LEFT)
		all->keys[4] = FALSE;
	else if (key == KEY_RIGHT)
		all->keys[5] = FALSE;
	else if (key == KEY_R)
		all->keys[6] = FALSE;
	else if (key == KEY_ESC)
		all->keys[7] = FALSE;
	return (0);
}

void	keys_handler(t_all *all)
{
	if (all->keys[0])
		move_player(all, 0);
	if (all->keys[1])
		move_player(all, M_PI);
	if (all->keys[2])
		move_player(all, M_PI_2);
	if (all->keys[3])
		move_player(all, -M_PI_2);
	if (all->keys[4])
		set_player_dir(all, all->plr.dir + ROTATE_SPEED);
	if (all->keys[5])
		set_player_dir(all, all->plr.dir - ROTATE_SPEED);
	if (all->keys[6])
	{
		set_player_pos(all, 26, 11);
		set_player_dir(all, M_PI_2);
	}
	if (all->keys[7])
	{
		clean_mlx(all);
		clean_map(all->map);
		free_malloc_pointers(all);
		exit(0);
	}
}
