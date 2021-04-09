/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 03:31:47 by emurky            #+#    #+#             */
/*   Updated: 2021/04/08 03:40:46 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_pnt
{
	int			x;
	int			y;
}				t_pnt;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
}				t_img;

typedef struct	s_plr
{
	double		x;
	double		y;
	double		dir;
	double		start;
	double		end;
}				t_plr;

typedef struct	s_all
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_plr		plr;
	char		**map;
}				t_all;

#endif