/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:42:02 by emurky            #+#    #+#             */
/*   Updated: 2021/04/13 03:36:52 by emurky           ###   ########.fr       */
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
# include "keys.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

#define TEST	"salam aleykum"

# define SCRN_W			1200
# define SCRN_H			900

# define MAP_OFFS_X		100
# define MAP_OFFS_Y		100

# define GRID			1
# define FOV			M_PI_2
# define SCALE			30
# define SPRITE_SCALE	2
# define MOVE_SPEED		SCALE / 4
# define ROTATE_SPEED	M_PI / 15

void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			is_player_dir(char c);
int			scaled_down_x(double index);
int			scaled_down_y(double index);
void		draw_ray(t_plr *ray, t_all *all, int color);
void		draw_square(t_img *img, int width, t_pnt pos, int color);
void		cast_rays(t_all *all, int raycount);
void		draw_map(t_all *all);
void		draw_player(t_all *all);

char		map_char(t_all *all);

#endif
