/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:23 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 03:11:59 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_init(t_all *all, t_ray *ray)
{
	ray->z_buff = NULL;
	ray->z_buff = malloc(sizeof(double) * all->screen.x);
	if (!ray->z_buff)
		leave(ERR, ERR_MALLOC, all, NULL);
	ray->sprites = NULL;
	ray->w = all->screen.x;
	ray->h = all->screen.y;
	ray->x = 0;
	ray->dir_x = cos(all->plr.dir);
	ray->dir_y = -sin(all->plr.dir);
	ray->pln_x = cos(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
	ray->pln_y = -sin(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
}

void	draw_floor_ceiling(t_all *all)
{
	int		i;
	int		j;

	j = 0;
	while (j <= all->screen.y / 2)
	{
		i = 0;
		while (i < all->screen.x)
		{
			my_mlx_pixel_put(&all->img, i, j, all->floor_ceil.y);
			i++;
		}
		j++;
	}
	while (j < all->screen.y)
	{
		i = 0;
		while (i < all->screen.x)
		{
			my_mlx_pixel_put(&all->img, i, j, all->floor_ceil.x);
			i++;
		}
		j++;
	}
}

void	draw_map(t_all *all)
{
	t_pnt	pos;

	pos.x = all->plr.x - SCALE / 2;
	pos.y = all->plr.y - SCALE / 2;
	draw_map_squares(all, all->map);
	draw_square(&all->img, SCALE, pos, AMBER);
	cast_rays(all, all->map, RAYCOUNT, SUNRAY);
	draw_ray(all, all->map, RED);
}

void	raycaster(t_all *all, t_ray *ray)
{
	ray_init(all, ray);
	draw_floor_ceiling(all);
	while (ray->x < ray->w)
	{
		ray_calc(ray);
		steps_increment(ray);
		perform_dda(all, ray);
		line_lenth_calc(ray);
		texturing(all, ray);
		ray->z_buff[ray->x] = ray->perpwalldist;
		ray->x++;
	}
	draw_sprites(all, ray);
	if (ray->z_buff)
		free(ray->z_buff);
	ray->z_buff = NULL;
}
