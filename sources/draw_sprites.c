/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:01:06 by emurky            #+#    #+#             */
/*   Updated: 2021/04/23 02:17:14 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sprites_counting(t_all *all)
{
	int		i;
	int		j;

	all->ray.num_sprs = 0;
	j = 0;
	while (all->map[j])
	{
		i = 0;
		while (all->map[j][i])
		{
			if (all->map[j][i] == '2')
				all->ray.num_sprs++;
			i++;
		}
		j++;
	}
	// printf("%d numSprites\n", all->ray.num_sprites);
}

void	sprites_init(t_all *all)
{
	(void)all;
	// all->spr_tex.img
	// 	= mlx_xpm_file_to_image(all->mlx, S, &all->spr_tex.w, &all->spr_tex.h);
	// all->spr_tex.addr
	// 	= mlx_get_data_addr(all->spr_tex.img, &all->spr_tex.bpp,
	// 		&all->spr_tex.linelen, &all->spr_tex.endian);
	// sprites_counting(all);
	// printf("%p in in sprites\n", (void *)all->spr.img);
}

void	sprites_pos_init(t_all *all, t_spr *sprites)
{
	int		i;
	int		j;
	int		s;

	s = 0;
	j = 0;
	while (all->map[j])
	{
		i = 0;
		while (all->map[j][i])
		{
			if (all->map[j][i] == '2')
			{
				sprites[s].x = i + 0.5;
				sprites[s].y = j + 0.5;
				s++;
			}
			i++;
		}
		j++;
	}
}

void	draw_sprites(t_all *all, t_ray *ray)
{
	ray->sprites = malloc(sizeof(t_spr) * ray->num_sprs);
	ray->spr_order = malloc(sizeof(int) * ray->num_sprs);
	ray->spr_dist = malloc(sizeof(double) * ray->num_sprs);
	if (!ray->sprites || !ray->spr_order || !ray->spr_dist)
		error();
	sprites_pos_init(all, ray->sprites);
	// for (int i = 0; i < ray->num_sprs; i++)
	// 	printf("%.1f posx %.1f posy #%d sprite\n", ray->sprites[i].x, ray->sprites[i].y, i + 1);

}
