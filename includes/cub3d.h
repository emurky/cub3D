/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:42:02 by emurky            #+#    #+#             */
/*   Updated: 2021/04/07 20:22:15 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"

#define TEST	"salam aleykum"

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
}				t_img;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_all
{
	void		*mlx;
	t_img		*img;
}				t_all;


#endif
