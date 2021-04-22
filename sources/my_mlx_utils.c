/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 02:22:08 by emurky            #+#    #+#             */
/*   Updated: 2021/04/22 03:31:19 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->linelen + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	clean_win(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < SCRN_W)
	{
		j = 0;
		while (j < SCRN_H)
		{
			my_mlx_pixel_put(all->img.img, i, j, BLACK);
			j++;
		}
		i++;
	}
}

void	frames_counter(t_all *all)
{
	char *counter;

	counter = ft_itoa(all->frames);
	all->frames++;
	mlx_string_put(all->mlx, all->win, SCRN_W - 50, 15, BLACK, counter);
	free(counter);
}
