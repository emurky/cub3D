/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 02:22:08 by emurky            #+#    #+#             */
/*   Updated: 2021/04/23 13:48:21 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		my_mlx_pixel_get(t_tex *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->linelen + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	my_mlx_tex_to_image(t_all *all, t_tex *tex, char *path)
{
	tex->img = NULL;
	tex->img
		= mlx_xpm_file_to_image(all->mlx, path, &tex->w, &tex->h);
	tex->addr
		= mlx_get_data_addr(tex->img, &tex->bpp, &tex->linelen, &tex->endian);
}

void	clean_win(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < all->screen.x)
	{
		j = 0;
		while (j < all->screen.y)
		{
			my_mlx_pixel_put(all->img.img, i, j, BLACK);
			j++;
		}
		i++;
	}
}

void	frames_counter(t_all *all)
{
	char	*counter;

	counter = ft_itoa(all->frames);
	all->frames++;
	mlx_string_put(all->mlx, all->win, all->screen.x - 50, 15, BLACK, counter);
	free(counter);
}
