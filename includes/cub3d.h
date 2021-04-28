/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:42:02 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 07:08:17 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# include "defines.h"
# include "structures.h"
# include "error.h"
# include "colors.h"
# include "keys.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

/*			cub3d.c */
void		structure_init(t_all *all);
void		frame_init(t_all *all);
int			renderer(t_all *all);
void		hooks_and_loops(t_all *all);

/*			my_mlx_utils.c */
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			my_mlx_pixel_get(t_tex *img, int x, int y);
void		my_mlx_tex_to_image(t_all *all, t_tex *tex, char **path);
void		mlx_start(t_all *all);
void		clean_mlx(t_all *all);

/*			parser.c */
int			check_all_identifiers(int *flags);
void		parse_identifiers(t_all *all, char **tokens);
void		parse_line(t_all *all, char *line);
void		parser(t_all *all, char *cub);

/*			parse_identifiers.c */
void		parse_resolution(t_all *all, char **tokens);
void		parse_texture(t_all *all, char **tokens, int dir);
void		check_and_skip_digits(int *rgb, int *i, t_all *all, char **tokens);
void		check_and_skip_spaces_and_comma(int *i, t_all *all, char **tokens);
void		parse_floor_ceil(t_all *all, char **tokens, int fc);

/*			set_parsed.c */
void		set_screen_size(t_all *all, char **tokens, int width, int height);
void		set_nswes(char **nswes, int *flag, char *token);
void		set_floor_ceil(t_all *all, char **tokens, int fc, int color);
void		init_player(t_all *all, char **map, int i, int j);
void		set_player(t_all *all, char **map);

/*			parse_map.c */
void		malloc_map(t_all *all, t_list **head);
void		make_map(t_all *all, t_list **head);
void		get_map_line(t_all *all, t_list **head, int line_read);
void		parse_map(t_all *all, int fd, int line_read);

/*			check_map.c */
int			is_interior(char c);
int			check_neighbours(t_map map, int row, int col);
int			check_continuity(t_map map);
int			check_map_line(t_all *all, char *line);

/*			parser_utils.c */
void		skip_spaces(int *i, t_all *all);
int			array_len(char **array);
int			str_isnum(char *str);
int			str_isspace(char *str);
int			isvalid_extension(char *file, const char *ext);

/*			player_move.c */
void		set_player_pos(t_all *all, int x, int y);
void		set_player_dir(t_all *all, double dir);
int			wall_collision_y(t_all *all, double dir);
int			wall_collision_x(t_all *all, double dir);
void		move_player(t_all *all, double dir);

/*			key_hooks.c */
int			print_key(int key, t_all *all);
int			close_window(t_all *all);
int			key_pressed(int key, t_all *all);
int			key_released(int key, t_all *all);
void		keys_handler(t_all *all);

/*			raycaster.c */
void		ray_init(t_all *all, t_ray *ray);
void		draw_floor_ceiling(t_all *all);
void		draw_map(t_all *all);
void		raycaster(t_all *all, t_ray *ray);

/*			raycasting_itself.c */
void		steps_increment(t_ray *ray);
void		ray_calc(t_ray *ray);
void		perform_dda(t_all *all, t_ray *ray);
void		line_lenth_calc(t_ray *ray);

/*			draw_map.c */
void		draw_square(t_img *img, int width, t_pnt pos, int color);
void		draw_ray(t_all *all, char **map, int color);
void		cast_rays(t_all *all, char **map, int raycount, int color);
void		draw_map_sprites(t_all *all, t_pnt *pos);
void		draw_map_squares(t_all *all, char **map);

/*			texturer.c */
void		textures_init(t_all *all);
void		which_nswe_wall_side(t_all *all, t_ray *ray, t_tex **tex);
void		textured_vert_line_h_calc(t_all *all, t_ray *ray, t_tex *tex);
void		texturing(t_all *all, t_ray *ray);

/*			draw_sprites.c */
void		sprites_init(t_all *all, t_ray *ray, t_spr *sprites);
void		sprites_projection(t_ray *ray, t_spr *sprites);
void		sprites_rendering(t_all *all, t_ray *ray);
void		draw_sprites(t_all *all, t_ray *ray);

/*			sprites_utils.c */
void		swap_sprites(t_spr *a, t_spr *b);
void		sprites_counting(t_all *all);
void		quicksort_sprites(t_spr *sprites, int first, int last);

/*			utils.c */
int			create_rgb(int r, int g, int b);
int			is_player_dir(char c);
int			scale_x(double index);
int			scale_y(double index);
void		is_enough_space_for_map(t_all *all);

/*			screenshot.c */
void		intset_little_endian(char *dest, uint32_t n, int size);
void		write_headers(t_all *all, int fd);
void		write_pixel_data(t_all *all, int fd);
void		save_screenshot(t_all *all);

/*			error.c */
void		free_array(char **array);
void		free_malloc_pointers(t_all *all);
void		clean_all(t_all *all);
void		print_error_exit(char *err_str);
void		leave(int error, char *err_str, t_all *all, char **array);

/*			unused.c */
void		fps(t_all *all);
void		frames_counter(t_all *all);
void		draw_vertical_line(t_ray *ray, t_img *img);

#endif
