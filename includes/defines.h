/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 08:02:05 by emurky            #+#    #+#             */
/*   Updated: 2021/04/27 06:24:55 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define TRUE			1
# define FALSE			0

# define R				0
# define NO				1
# define SO				2
# define WE				3
# define EA				4
# define S				5
# define F				6
# define C				7
# define ISMAP_OK		8
# define EOM			9 /* end of map */
# define XPM			10
# define PNG			11

# define FOV			M_PI / 3
# define MOVE_SPEED		0.05
# define ROTATE_SPEED	M_PI / 90

# define DRAW_MAP		TRUE
# define MAP_OFFS_X		10
# define MAP_OFFS_Y		10
# define GRID			TRUE
# define SCALE			10
# define SPRITE_SCALE	2
# define RAYCOUNT		SCALE * 3

# define UDIV			1.0
# define VDIV			1.0
# define VMOVE			64.0

#endif
