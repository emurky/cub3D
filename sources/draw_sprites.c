/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:01:06 by emurky            #+#    #+#             */
/*   Updated: 2021/04/22 23:43:46 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sprites_counting(t_all *all)
{
	int		i;
	int		j;

	all->ray.num_sprites = 0;
	j = 0;
	while (all->map[j])
	{
		i = 0;
		while (all->map[j][i])
		{
			if (all->map[j][i] == '2')
				all->ray.num_sprites++;
			i++;
		}
		j++;
	}
	// printf("%d numSprites\n", all->ray.num_sprites);
}

void	sprites_init(t_all *all)
{
	all->spr.img
		= mlx_xpm_file_to_image(all->mlx, S, &all->spr.w, &all->spr.h);
	all->spr.addr
		= mlx_get_data_addr(all->spr.img, &all->spr.bpp,
			&all->spr.linelen, &all->spr.endian);
	// printf("%p in in sprites\n", (void *)all->spr.img);
}

void	draw_sprites(t_all *all, t_ray *ray)
{
	(void)all;
	(void)ray;
}
