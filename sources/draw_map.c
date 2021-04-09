/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:43:36 by emurky            #+#    #+#             */
/*   Updated: 2021/04/09 04:44:24 by emurky           ###   ########.fr       */
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
	while (j < width + pos.y)
	{
		i = pos.x;
		while (i < width + pos.x)
		{
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_ray(/*t_all *all, double x, double y*/)
{

}

void	cast_rays(t_all *all, int raycount)
{
	t_plr	ray;
	double	start;
	double	end;

	ray = all->plr;
	start = ray.dir - M_PI_4;
	end = ray.dir + M_PI_4;
	raycount--;
	while (start <= end)
	{
		ray.x = all->plr.x;
		ray.y = all->plr.y;
		while (all->map[scaled_down_y(ray.y)][scaled_down_x(ray.x)] != '1')
		{
			ray.x += cos(start);
			ray.y -= sin(start);
			my_mlx_pixel_put(&all->img, ray.x, ray.y, BLUE);
		}
		start += M_PI_2 / raycount;
	}
}

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
			else if (is_player_dir(all->map[i][j]))
				draw_square(&all->img, SCALE, pos, RED);
			else
				draw_square(&all->img, SCALE, pos, DARK_GREY);
			pos.x += SCALE;
			j++;
		}
		pos.y += SCALE;
		i++;
	}
	cast_rays(all, 88);
}
