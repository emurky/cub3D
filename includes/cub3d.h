/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:42:02 by emurky            #+#    #+#             */
/*   Updated: 2021/04/08 16:15:42 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# include "structures.h"
# include "colors.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

#define TEST	"salam aleykum"

void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			is_player_dir(char c);
int			scaled_down_x(double index);
void		draw_square(t_img *img, int width, t_pnt pos, int color);
void		cast_rays(t_all *all, int raycount);
void		draw_map(t_all *all);


#endif
