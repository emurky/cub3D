/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:23 by emurky            #+#    #+#             */
/*   Updated: 2021/04/23 13:48:57 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_init(t_all *all, t_ray *ray)
{
	ray->z_buff = NULL;
	ray->z_buff = malloc(sizeof(double) * all->screen.x);
	if (!ray->z_buff)
		error();
	ray->sprites = NULL;
	ray->w = all->screen.x;
	ray->h = all->screen.y;
	ray->x = 0;
	ray->dir_x = cos(all->plr.dir);
	ray->dir_y = -sin(all->plr.dir);
	ray->pln_x = cos(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
	ray->pln_y = -sin(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
	// printf("%.2f dirx %.2f diry\n%.2f pnlx %.2f plny\n", ray->dir_x, ray->dir_y, ray->pln_x, ray->pln_y);
}

void	steps_increment(t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x - ray->pos_x + 1.0) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y - ray->pos_y + 1.0) * ray->deltadist_y;
	}
}

void	ray_calc(t_ray *ray)
{
	ray->cam_x = 2 * (double)(ray->x) / (double)(ray->w) - 1;
	ray->raydir_x = ray->dir_x + ray->pln_x * ray->cam_x;
	ray->raydir_y = ray->dir_y + ray->pln_y * ray->cam_x;
	ray->map_x = (int)(ray->pos_x);
	ray->map_y = (int)(ray->pos_y);
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}

void	perform_dda(t_all *all, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (all->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	line_lenth_calc(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perpwalldist
			= (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
	}
	else
	{
		ray->perpwalldist
			= (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;
	}
	ray->line_h = (int)(ray->h / ray->perpwalldist);
	ray->draw_start = -ray->line_h / 2 + ray->h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + ray->h / 2;
	if (ray->draw_end >= ray->h)
		ray->draw_end = ray->h - 1;
}

void	draw_vertical_line(t_ray *ray, t_img *img)
{
	int		color;

	color = RED;
	if (ray->side == 1)
		color /= 2;
	while (ray->draw_start <= ray->draw_end)
	{
		my_mlx_pixel_put(img, ray->x, ray->draw_start, color);
		ray->draw_start++;
	}
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
		// draw_vertical_line(ray, &all->img);
		texturing(all, ray);
		ray->z_buff[ray->x] = ray->perpwalldist;
		ray->x++;
	}
	draw_sprites(all, ray);
	draw_map(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	if (ray->z_buff)
		free(ray->z_buff);
	ray->z_buff = NULL;
}
