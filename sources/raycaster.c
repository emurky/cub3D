/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:23 by emurky            #+#    #+#             */
/*   Updated: 2021/04/20 23:06:56 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dda_init(t_all *all, t_dda *dda)
{
	dda->w = SCRN_W;
	dda->h = SCRN_H;
	dda->i = dda->w - 1;
	// dda->pos_x = all->plr_init.x;
	// dda->pos_y = all->plr_init.y;
	dda->dir_x = cos(all->plr.dir);
	dda->dir_y = -sin(all->plr.dir);
	dda->pln_x = cos(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
	dda->pln_y = -sin(all->plr.dir - M_PI_2) * round(FOV * 180 / M_PI) / 100;
}

void	steps_increment(t_dda *dda)
{
	if (dda->raydir_x < 0)
	{
		dda->step_x = -1;
		dda->sidedist_x = (dda->pos_x - dda->map_x) * dda->deltadist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->sidedist_x = (dda->map_x - dda->pos_x + 1.0) * dda->deltadist_x;
	}
	if (dda->raydir_y < 0)
	{
		dda->step_y = -1;
		dda->sidedist_y = (dda->pos_y - dda->map_y) * dda->deltadist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->sidedist_y = (dda->map_y - dda->pos_y + 1.0) * dda->deltadist_y;
	}
}

void	ray_calc(t_dda *dda)
{
	dda->cam_x = 2 * (double)(dda->i) / (double)(dda->w) - 1;
	dda->raydir_x = dda->dir_x + dda->pln_x * dda->cam_x;
	dda->raydir_y = dda->dir_y + dda->pln_y * dda->cam_x;
	dda->map_x = (int)(dda->pos_x);
	dda->map_y = (int)(dda->pos_y);
	dda->deltadist_x = fabs(1 / dda->raydir_x);
	dda->deltadist_y = fabs(1 / dda->raydir_y);
	dda->hit = 0;
}

void	perform_dda(t_all *all, t_dda *dda)
{
	while (dda->hit == 0)
	{
		if (dda->sidedist_x < dda->sidedist_y)
		{
			dda->sidedist_x += dda->deltadist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->sidedist_y += dda->deltadist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (all->map[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
		// printf("%c map char\n", all->map[dda->map_y][dda->map_x]);
	}
}

void	line_lenth_calc(t_dda *dda)
{
	if (dda->side == 0)
		dda->perpwalldist
			= (dda->map_x - dda->pos_x + (1 - dda->step_x) / 2) / dda->raydir_x;
	else
		dda->perpwalldist
			= (dda->map_y - dda->pos_y + (1 - dda->step_y) / 2) / dda->raydir_y;
	dda->line_h = (int)(dda->h / dda->perpwalldist);
	dda->draw_start = -dda->line_h / 2 + dda->h / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = dda->line_h / 2 + dda->h / 2;
	if (dda->draw_end >= dda->h)
		dda->draw_end = dda->h - 1;
}

void	draw_vertical_line(t_dda *dda, t_img *img, int color)
{
	while (dda->draw_start <= dda->draw_end)
	{
		my_mlx_pixel_put(img, dda->i, dda->draw_start, color);
		dda->draw_start++;
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

void	raycaster(t_all *all, t_dda *dda)
{
	dda_init(all, dda);
	draw_floor_ceiling(all, SKY_BLUE, BORDEAUX);
	while (dda->i >= 0)
	{
		ray_calc(dda);
		steps_increment(dda);
		perform_dda(all, dda);
		line_lenth_calc(dda);
		int color = RED;
		if (dda->side == 1)
										{color /= 2;}
		draw_vertical_line(dda, &all->img, color);
		dda->i--;
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	// dda.i = 20;
	// dda.draw_start = 0;
	// dda.draw_end = 800;
	// draw_vertical_line(&dda, &all->img, BLUE);
	// printf("%f\n", dda->pln_y);
	// printf("%f posx %f posy\n", all->plr.start, all->plr.end);
}
