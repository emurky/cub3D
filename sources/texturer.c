/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 02:25:39 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 02:12:06 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	textures_init(t_all *all)
{
	my_mlx_tex_to_image(all, &all->tex[0], &all->nswes.no);
	my_mlx_tex_to_image(all, &all->tex[1], &all->nswes.so);
	my_mlx_tex_to_image(all, &all->tex[2], &all->nswes.we);
	my_mlx_tex_to_image(all, &all->tex[3], &all->nswes.ea);
	my_mlx_tex_to_image(all, &all->tex[4], &all->nswes.s);
}

void	which_nswe_wall_side(t_all *all, t_ray *ray, t_tex **tex)
{
	if (ray->side == 1)
	{
		if (ray->raydir_y > 0)
			*tex = &all->tex[1];
		else
			*tex = &all->tex[0];
	}
	else
	{
		if (ray->raydir_x > 0)
			*tex = &all->tex[3];
		else
			*tex = &all->tex[2];
	}
}

void	textured_vert_line_h_calc(t_all *all, t_ray *ray, t_tex *tex)
{
	if (ray->side == 0)
		ray->wall_x = ray->pos_y + ray->perpwalldist * ray->raydir_y;
	else
		ray->wall_x = ray->pos_x + ray->perpwalldist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)tex->w);
	if ((ray->side == 0 && ray->raydir_x < 0)
		|| (ray->side == 1 && ray->raydir_y > 0))
		ray->tex_x = tex->w - ray->tex_x - 1;
	ray->tex_step = 1.0 * tex->h / ray->line_h;
	ray->tex_pos
		= (ray->draw_start - ray->h / 2 + ray->line_h / 2) * ray->tex_step;
	ray->y = ray->draw_start;
	while (ray->y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
		ray->tex_pos += ray->tex_step;
		ray->pixel = my_mlx_pixel_get(tex, ray->tex_x, ray->tex_y);
		my_mlx_pixel_put(&all->img, ray->x, ray->y, ray->pixel);
		ray->y++;
	}
}

void	texturing(t_all *all, t_ray *ray)
{
	t_tex	*tex;

	which_nswe_wall_side(all, ray, &tex);
	textured_vert_line_h_calc(all, ray, tex);
}
