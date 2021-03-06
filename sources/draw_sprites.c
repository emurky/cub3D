/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:01:06 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 03:09:59 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sprites_init(t_all *all, t_ray *ray, t_spr *sprites)
{
	int		i;
	int		j;
	int		s;

	s = 0;
	j = 0;
	ray->s_i = 0;
	while (all->map[j])
	{
		i = 0;
		while (all->map[j][i])
		{
			if (all->map[j][i] == '2')
			{
				sprites[s].x = i + 0.5;
				sprites[s].y = j + 0.5;
				sprites[s].order = s;
				sprites[s].dist = (pow(ray->pos_x - sprites[s].x, 2)
						+ pow(ray->pos_y - sprites[s].y, 2));
				s++;
			}
			i++;
		}
		j++;
	}
}

void	sprites_projection(t_ray *ray, t_spr *sprites)
{
	ray->spr_x = sprites[ray->s_i].x - ray->pos_x;
	ray->spr_y = sprites[ray->s_i].y - ray->pos_y;
	ray->inv_det = 1.0 / (ray->pln_x * ray->dir_y - ray->dir_x * ray->pln_y);
	ray->transf_x = ray->inv_det
		* (ray->dir_y * ray->spr_x - ray->dir_x * ray->spr_y);
	ray->transf_y = ray->inv_det
		* (-ray->pln_y * ray->spr_x + ray->pln_x * ray->spr_y);
	ray->sprscrn_x = (int)((ray->w / 2) * (1 + ray->transf_x / ray->transf_y));
	ray->v_move_scrn = (int)(VMOVE / ray->transf_y);
	ray->spr_h = (int)fabs(ray->h / ray->transf_y) * VDIV * ray->k;
	ray->dr_start_y = -ray->spr_h / 2 + ray->h / 2 + ray->v_move_scrn;
	if (ray->dr_start_y < 0)
		ray->dr_start_y = 0;
	ray->dr_end_y = ray->spr_h / 2 + ray->h / 2 + ray->v_move_scrn;
	if (ray->dr_end_y >= ray->h)
		ray->dr_end_y = ray->h - 1;
	ray->spr_w = (int)fabs(ray->h / ray->transf_y) * UDIV * ray->k;
	ray->dr_start_x = -ray->spr_w / 2 + ray->sprscrn_x;
	if (ray->dr_start_x < 0)
		ray->dr_start_x = 0;
	ray->dr_end_x = ray->spr_w / 2 + ray->sprscrn_x;
	if (ray->dr_end_x >= ray->w)
		ray->dr_end_x = ray->w - 1;
}

void	sprites_rendering(t_all *all, t_ray *ray)
{
	ray->x = ray->dr_start_x;
	ray->y = ray->dr_start_y;
	while (ray->x < ray->dr_end_x)
	{
		ray->s_tex_x = (int)(256 * (ray->x - (-ray->spr_w / 2
						+ ray->sprscrn_x)) * all->tex[4].w / ray->spr_w) / 256;
		if (ray->transf_y > 0 && ray->x > 0 && ray->x < ray->w
			&& ray->transf_y < ray->z_buff[ray->x]
			&& ray->sprites[ray->s_i].dist >= 0.5)
		{
			ray->y = ray->dr_start_y;
			while (ray->y < ray->dr_end_y)
			{
				ray->d = (int)fabs((double)((ray->y - ray->v_move_scrn) * 256
							- ray->h * 128 + ray->spr_h * 128));
				ray->s_tex_y = ((ray->d * all->tex[4].h) / ray->spr_h) / 256;
				ray->pixel = my_mlx_pixel_get
					(&all->tex[4], ray->s_tex_x, ray->s_tex_y);
				if ((ray->pixel & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&all->img, ray->x, ray->y, ray->pixel);
				ray->y++;
			}
		}
		ray->x++;
	}
}

void	draw_sprites(t_all *all, t_ray *ray)
{
	ray->sprites = malloc(sizeof(t_spr) * ray->num_sprs);
	if (!ray->sprites)
		leave(ERR, ERR_MALLOC, all, NULL);
	sprites_init(all, ray, ray->sprites);
	quicksort_sprites(ray->sprites, 0, ray->num_sprs - 1);
	while (ray->s_i < ray->num_sprs)
	{
		sprites_projection(ray, ray->sprites);
		sprites_rendering(all, ray);
		ray->s_i++;
	}
	if (ray->sprites)
		free(ray->sprites);
	ray->sprites = NULL;
	if (all->ray.z_buff)
		free(all->ray.z_buff);
	all->ray.z_buff = NULL;
}
