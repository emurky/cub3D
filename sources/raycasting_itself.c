/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_itself.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:10:50 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 03:11:43 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	ray->line_h = (int)(ray->h / ray->perpwalldist * ray->k);
	ray->draw_start = -ray->line_h / 2 + ray->h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + ray->h / 2;
	if (ray->draw_end >= ray->h)
		ray->draw_end = ray->h - 1;
}
