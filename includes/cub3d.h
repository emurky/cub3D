/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:42:02 by emurky            #+#    #+#             */
/*   Updated: 2021/04/20 22:53:19 by emurky           ###   ########.fr       */
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

# define TRUE			1
# define FALSE			0

# define SCRN_W			1200
# define SCRN_H			900

# define MAP_OFFS_X		20
# define MAP_OFFS_Y		20

# define GRID			TRUE
# define FOV			M_PI / 3
# define SCALE			10
# define SPRITE_SCALE	2

# define RAYCOUNT		SCALE * 3
# define MOVE_SPEED		SCALE / 3
# define ROTATE_SPEED	M_PI / 16

/*			utils.c */
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			is_player_dir(char c);
void		set_player_pos(t_all *all, int x, int y);
void		set_player_dir(t_all *all, double dir);
void		move_player(t_all *all, double dir);
int			scaled_down_x(double index);
int			scaled_down_y(double index);
char		map_char(t_all *all);
int			wall_collision(t_all *all, double angle);

/*			draw_map.c */
void		draw_square(t_img *img, int width, t_pnt pos, int color);
void		draw_ray(t_all *all, int color);
void		cast_rays(t_all *all, int raycount);
void		draw_sprites(t_all *all, t_pnt *pos);
void		draw_map(t_all *all);
void		draw_player(t_all *all);

/*			key_hooks.c */
int			print_key(int key, t_all *all);
int			esc_exit(int key, t_all *all);
int			close_window(t_all *all);
void		key_press(int key, t_all *all);

void		raycaster(t_all *all, t_dda *dda);

void	clean_map(char **map);

#endif
