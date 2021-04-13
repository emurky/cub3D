/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:43:36 by emurky            #+#    #+#             */
/*   Updated: 2021/04/13 04:10:10 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_rectangle(t_img *img, int width, int height, int color)
{
	int		i;
	int		j;

	i = MAP_OFFS_X;
	j = MAP_OFFS_Y;
	while (j <= height + MAP_OFFS_Y)
	{
		i = MAP_OFFS_X;
		while (i <= width + MAP_OFFS_X)
		{
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_square(t_img *img, int width, t_pnt pos, int color)
{
	int		i;
	int		j;

	j = pos.y;
	while (j < width + pos.y - GRID)
	{
		i = pos.x;
		while (i < width + pos.x - GRID)
		{
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_ray(t_plr *ray, t_all *all, int color)
{
	while (all->map[scaled_down_y(ray->y)][scaled_down_x(ray->x)] != '1')
	{
		ray->x += cos(ray->dir);
		ray->y -= sin(ray->dir);
		my_mlx_pixel_put(&all->img, ray->x, ray->y, color);
	}
}

void	cast_rays(t_all *all, int raycount)
{
	t_plr	ray;

	ray = all->plr;
	raycount--;
	while (ray.start <= ray.end)
	{
		ray.x = all->plr.x;
		ray.y = all->plr.y;
		while (all->map[scaled_down_y(ray.y)][scaled_down_x(ray.x)] != '1')
		{
			ray.x += cos(ray.start);
			ray.y -= sin(ray.start);
			my_mlx_pixel_put(&all->img, ray.x, ray.y, BLUE);
		}
		ray.start += FOV / raycount;
	}
}

// void	draw_sprites(t_all *all, t_pnt *pos)
// {
// 	draw_square(&all->img, SCALE, *pos, DARK_GREY);
// 	pos->x += (SCALE - SCALE / SPRITE_SCALE) / 2;
// 	pos->y += (SCALE - SCALE / SPRITE_SCALE) / 2;
// 	draw_square(&all->img, SCALE / SPRITE_SCALE, *pos, RED);
// 	pos->x -= (SCALE - SCALE / SPRITE_SCALE) / 2;
// 	pos->y -= (SCALE - SCALE / SPRITE_SCALE) / 2;
// }

void	draw_map(t_all *all)
{
	int		i;
	int		j;
	t_pnt	pos;

	i = 0;
	pos.y = MAP_OFFS_Y;
	while (all->map[i])
	{
		j = 0;
		pos.x = MAP_OFFS_X;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				draw_square(&all->img, SCALE, pos, WHITE);
			// else if (is_player_dir(all->map[i][j]))
			// 	draw_square(&all->img, SCALE, pos, GREEN);
			else if (all->map[i][j] == '2')
			{
				draw_square(&all->img, SCALE, pos, DARK_GREY);
				pos.x += (SCALE - SCALE / SPRITE_SCALE) / 2;
				pos.y += (SCALE - SCALE / SPRITE_SCALE) / 2;
				draw_square(&all->img, SCALE / SPRITE_SCALE, pos, RED);
				pos.x -= (SCALE - SCALE / SPRITE_SCALE) / 2;
				pos.y -= (SCALE - SCALE / SPRITE_SCALE) / 2;
			}
			else
				draw_square(&all->img, SCALE, pos, DARK_GREY);
			pos.x += SCALE;
			j++;
		}
		pos.y += SCALE;
		i++;
	}
}

void	draw_player(t_all *all)
{
	t_pnt	pos;

	pos.x = all->plr.x - SCALE / 2;
	pos.y = all->plr.y - SCALE / 2;
	draw_map(all);
	draw_square(&all->img, SCALE, pos, GREEN);
	cast_rays(all, RAYCOUNT);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}
