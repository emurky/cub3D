/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:23 by emurky            #+#    #+#             */
/*   Updated: 2021/04/22 01:26:32 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_init(t_all *all, t_ray *ray)
{
	ray->w = SCRN_W;
	ray->h = SCRN_H;
	ray->x = ray->w - 1;
	ray->dir_x = cos(all->plr.dir);
	ray->dir_y = -sin(all->plr.dir);
	ray->pln_x = cos(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
	ray->pln_y = -sin(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
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
		// printf("%c map char\n", all->map[ray->map_y][ray->map_x]);
	}
}

void	line_lenth_calc(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist
			= (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perpwalldist
			= (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;
	ray->line_h = (int)(ray->h / ray->perpwalldist);
	ray->draw_start = -ray->line_h / 2 + ray->h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + ray->h / 2;
	if (ray->draw_end >= ray->h)
		ray->draw_end = ray->h - 1;
}

void	draw_vertical_line(t_ray *ray, t_img *img, int color)
{
	while (ray->draw_start <= ray->draw_end)
	{
		my_mlx_pixel_put(img, ray->x, ray->draw_start, color);
		ray->draw_start++;
	}
}

void	draw_floor_ceiling(t_all *all, int col_ceil, int col_floor)
{
	int		i;
	int		j;

	j = 0;
	while (j <= SCRN_H / 2)
	{
		i = 0;
		while (i < SCRN_W)
		{
			my_mlx_pixel_put(&all->img, i, j, col_ceil);
			i++;
		}
		j++;
	}
	while (j < SCRN_H)
	{
		i = 0;
		while (i < SCRN_W)
		{
			my_mlx_pixel_put(&all->img, i, j, col_floor);
			i++;
		}
		j++;
	}
}

void	test_tex(t_all *all)
{
	// void	*tex;
	t_img	tex;
	int		i;
	int		j;
	int		w;
	int		h;
	int		color;

	i = 0;
	tex.img = mlx_xpm_file_to_image(all->mlx, NO, &w, &h);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.linelen, &tex.endian);
	
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			color = my_mlx_pixel_get(&tex, i, j);
			my_mlx_pixel_put(&all->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	textures_init(t_all *all)
{
	all->tex[0].img.img = mlx_xpm_file_to_image(all->mlx, NO, &all->tex[0].w, &all->tex[0].h);
	all->tex[0].img.addr = mlx_get_data_addr(all->tex[0].img.img, &all->tex[0].img.bpp, &all->tex[0].img.linelen, &all->tex[0].img.endian);

	all->tex[1].img.img = mlx_xpm_file_to_image(all->mlx, SO, &all->tex[1].w, &all->tex[1].h);
	all->tex[1].img.addr = mlx_get_data_addr(all->tex[1].img.img, &all->tex[1].img.bpp, &all->tex[1].img.linelen, &all->tex[1].img.endian);

	all->tex[2].img.img = mlx_xpm_file_to_image(all->mlx, WE, &all->tex[2].w, &all->tex[2].h);
	all->tex[2].img.addr = mlx_get_data_addr(all->tex[2].img.img, &all->tex[2].img.bpp, &all->tex[2].img.linelen, &all->tex[2].img.endian);

	all->tex[3].img.img = mlx_xpm_file_to_image(all->mlx, EA, &all->tex[3].w, &all->tex[3].h);
	all->tex[3].img.addr = mlx_get_data_addr(all->tex[3].img.img, &all->tex[3].img.bpp, &all->tex[3].img.linelen, &all->tex[3].img.endian);

// 	// (all->tex).img.img = mlx_xpm_file_to_image(all->mlx, NO, &(all->tex).w, &(all->tex).h);
// 	// (all->tex).img.addr = mlx_get_data_addr(&(all->tex).img, &(all->tex).img.bpp,
// 	// 		&(all->tex).img.linelen, &(all->tex).img.endian);
// 	int		i;
// 	t_tex	*tex;
// 	t_img	*img;
// int w, h;
// 	i = 0;
// 	// while (i < 4)
// 	// {
// 		tex = &all->tex[i];
// 		img = &tex->img;
// 		printf("tut\n");
// 		img->img = mlx_xpm_file_to_image(all->mlx, NO, &w, &h);
// 		tex->img.addr = mlx_get_data_addr(&tex->img, &tex->img.bpp,
// 			&tex->img.linelen, &tex->img.endian);
// 		// i++;
// 	// }
// // 	tex[0]->img.img = mlx_xpm_file_to_image(all->mlx, NO, &tex[0]->w, &tex[0]->h);
// // 	tex[0]->img.addr = mlx_get_data_addr(&tex[0]->img, &tex[0]->img.bpp,
// // 			&tex[0]->img.linelen, &tex[0]->img.endian);
// // printf("tut\n");
// // 	tex[1]->img.img = mlx_xpm_file_to_image(all->mlx, SO, &tex[1]->w, &tex[1]->h);
// // 	tex[1]->img.addr = mlx_get_data_addr(&tex[1]->img, &tex[1]->img.bpp,
// // 			&tex[1]->img.linelen, &tex[1]->img.endian);
// // 	tex[2]->img.img = mlx_xpm_file_to_image(all->mlx, WE, &tex[2]->w, &tex[2]->h);
// // 	tex[2]->img.addr = mlx_get_data_addr(&tex[2]->img, &tex[2]->img.bpp,
// // 			&tex[2]->img.linelen, &tex[2]->img.endian);
// // 	tex[3]->img.img = mlx_xpm_file_to_image(all->mlx, EA, &tex[3]->w, &tex[3]->h);
// // 	tex[3]->img.addr = mlx_get_data_addr(&tex[3]->img, &tex[3]->img.bpp,
// // 			&tex[3]->img.linelen, &tex[3]->img.endian);
}

void	texturing(t_all *all, t_ray *ray)
{
	t_tex	*tex;
	int		pixel;
	int		y;

	tex = NULL;
	if (ray->side == 1)
	{
		if (ray->raydir_y > 0)
			tex = &all->tex[1];
		else
			tex = &all->tex[0];
	}
	else if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			tex = &all->tex[3];
		else
			tex = &all->tex[2];
	}
	if (ray->side == 0)
		ray->wall_x = ray->pos_y + ray->perpwalldist * ray->raydir_y;
	else
		ray->wall_x = ray->pos_x + ray->perpwalldist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)tex->w);
	if ((ray->side == 0 && ray->raydir_x > 0)
		|| (ray->side == 1 && ray->raydir_y < 0))
		ray->tex_x = tex->w - ray->tex_x - 1;
	ray->tex_step = 1.0 * tex->h / ray->line_h;
	ray->tex_pos = (ray->draw_start - ray->h / 2 + ray->line_h / 2) * ray->tex_step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
		ray->tex_pos += ray->tex_step;
		
		pixel = my_mlx_pixel_get(&tex->img, ray->tex_x, ray->tex_y);
		my_mlx_pixel_put(&all->img, ray->x, y, pixel);
		y++;
	}
}

void	raycaster(t_all *all, t_ray *ray)
{
	ray_init(all, ray);
	draw_floor_ceiling(all, SKY_BLUE, BORDEAUX);
	while (ray->x >= 0)
	{
		ray_calc(ray);
		steps_increment(ray);
		perform_dda(all, ray);
		line_lenth_calc(ray);
		// int color = RED;
		// if (ray->side == 1)
		// 								{color /= 2;}
		// draw_vertical_line(ray, &all->img, color);
		texturing(all, ray);
		ray->x--;
	}
	draw_map(all);
	// test_tex(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	// ray.i = 20;
	// ray.draw_start = 0;
	// ray.draw_end = 800;
	// draw_vertical_line(&ray, &all->img, BLUE);
	// printf("%f\n", ray->pln_y);
	// printf("%f posx %f posy\n", all->plr.start, all->plr.end);
}
