/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:42:02 by emurky            #+#    #+#             */
/*   Updated: 2021/04/25 17:10:06 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

#include <time.h> //UDOLITB

# include "structures.h"
# include "error.h"
# include "colors.h"
# include "keys.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

#define	DB printf("tut\n");

# define TRUE			1
# define FALSE			0

# define SCRN_W			1200 // should be get from *.cub
# define SCRN_H			900

# define MAP_OFFS_X		20
# define MAP_OFFS_Y		20

# define GRID			TRUE
# define FOV			M_PI / 3
# define SCALE			10
# define SPRITE_SCALE	2

# define RAYCOUNT		SCALE * 3
# define MOVE_SPEED		0.05
# define ROTATE_SPEED	M_PI / 180

# define UDIV			1.0
# define VDIV			1.0
# define VMOVE			64.0

# define NO		"textures/redbrick.xpm"
# define SO		"textures/greystone.xpm"
# define WE		"textures/colorstone.xpm"
# define EA		"textures/wood.xpm"
# define S		"textures/barrel.xpm"


/*			my_mlx_utils.c */
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			my_mlx_pixel_get(t_tex *img, int x, int y);
void		my_mlx_tex_to_image(t_all *all, t_tex *tex, char *path);
void		clean_win(t_all *all);
void		frames_counter(t_all *all);

/*			utils.c */
int			ft_strcmp(const char *s1, const char *s2);

int			is_player_dir(char c);

/*			error.c */
void		clean_map(char **map);
void		free_malloc_pointers(t_all *all);
void		clean_mlx(t_all *all);
void		print_error_exit(char *err_str);
void		leave(int error, char *err_str, t_all *all);

/*			player_movement.c */
void		set_player_pos(t_all *all, int x, int y);
void		set_player_dir(t_all *all, double dir);
void		move_player(t_all *all, double dir);
int			scale_x(double index);
int			scale_y(double index);

/*			key_hooks.c */
int			print_key(int key, t_all *all);
int			close_window(t_all *all);
int			key_pressed(int key, t_all *all);
int			key_released(int key, t_all *all);
void		keys_handler(t_all *all);

/*			draw_map.c */
void		draw_square(t_img *img, int width, t_pnt pos, int color);
void		draw_ray(t_all *all, int color);
void		cast_rays(t_all *all, int raycount, int color);
void		draw_map_sprites(t_all *all, t_pnt *pos);
void		draw_map_squares(t_all *all);
void		draw_map(t_all *all);

/*			texturer.c */
void		textures_init(t_all *all);
void		which_nswe_wall_side(t_all *all, t_ray *ray, t_tex **tex);
void		textured_vert_line_h_calc(t_all *all, t_ray *ray, t_tex *tex);
void		texturing(t_all *all, t_ray *ray);

/*			draw_sprites.c */
void		sprites_counting(t_all *all);
void		sprites_init(t_all *all, t_ray *ray, t_spr *sprites);
void		draw_sprites(t_all *all, t_ray *ray);

/*			raycaster.c */
void		ray_init(t_all *all, t_ray *ray);
void		steps_increment(t_ray *ray);
void		ray_calc(t_ray *ray);
void		perform_dda(t_all *all, t_ray *ray);
void		line_lenth_calc(t_ray *ray);
void		draw_vertical_line(t_ray *ray, t_img *img);
void		draw_floor_ceiling(t_all *all);
void		raycaster(t_all *all, t_ray *ray);

#endif
