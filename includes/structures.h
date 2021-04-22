/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 03:31:47 by emurky            #+#    #+#             */
/*   Updated: 2021/04/22 23:13:24 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_pnt
{
	int			x;
	int			y;
}				t_pnt;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
}				t_img;

typedef struct s_plr
{
	double		x;
	double		y;
	double		dir;
	double		start;
	double		end;
}				t_plr;

// typedef struct s_plr_init
// {
// 	int			x;
// 	int			y;
// 	double		dir;
// }				t_plr_init;

typedef struct s_ray
{
	int			w;
	int			h;
	int			x;
	int			y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		pln_x;
	double		pln_y;
	double		cam_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perpwalldist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		tex_step;
	double		tex_pos;
	int			pixel;
	int			num_sprites;
}				t_ray;

typedef struct s_tex
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
	int			w;
	int			h;
}				t_tex;

typedef struct s_spr
{
	double		x;
	double		y;
	
}								t_spr;

typedef struct s_pths
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
}				t_pths;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_img		img;

	t_pnt		screen;
	t_pths		nswes;
	t_tex		tex[4];
	t_tex		spr;
	t_pnt		floor_ceil;
	char		**map;

	t_plr		plr;
	t_ray		ray;

	int			frames;
}				t_all;

#endif
