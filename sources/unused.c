/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:47:54 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 03:12:23 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* from <time.h> clock(), frame_time should be divided by CLOCK_PER_SEC */
void	fps(t_all *all)
{
	int		old_time;
	double	frame_time;
	char	*fps;
	int		clock;

	clock = 0;
	fps = NULL;
	old_time = all->time;
	all->time = (double)clock;
	frame_time = (all->time - old_time) / 1;
	fps = ft_itoa((int)round(1 / frame_time));
	mlx_string_put(all->mlx, all->win, all->screen.x - 50, 15, BLACK, fps);
	all->move_speed = frame_time * 4.0;
	all->rotate_speed = frame_time * 1.5;
	if (fps)
		free(fps);
}

void	frames_counter(t_all *all)
{
	char	*counter;

	counter = NULL;
	counter = ft_itoa(all->frames);
	all->frames++;
	mlx_string_put(all->mlx, all->win, all->screen.x - 50, 15, BLACK, counter);
	if (counter)
		free(counter);
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
