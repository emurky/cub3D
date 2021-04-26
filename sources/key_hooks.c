/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:50:33 by emurky            #+#    #+#             */
/*   Updated: 2021/04/26 01:02:24 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		print_key(int key, t_all *all)
{
	(void)all;
	printf("%d was pressed\n", key);
	return (0);
}

int		close_window(t_all *all)
{
	leave(NO_ERR, NULL, all, NULL);
	return (0);
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
		leave(NO_ERR, NULL, all, NULL);
}
