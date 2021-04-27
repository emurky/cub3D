/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 08:02:05 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 01:41:17 by emurky           ###   ########.fr       */
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
# define EOM			9			/* end of map */
# define PLR			10
# define XPM			11
# define PNG			12

# define FOV			1.0472		/* M_PI / 3 */
# define MOVE_SPEED		0.03
# define ROTATE_SPEED	0.02		/* M_PI / 180 */

# define DRAW_MAP		TRUE
# define MAP_OFFS_X		10
# define MAP_OFFS_Y		10
# define GRID			TRUE
# define SCALE			10
# define SPRITE_SCALE	2
# define RAYCOUNT		30			/* SCALE * 3 */

# define UDIV			1.0
# define VDIV			1.0
# define VMOVE			64.0

# define HEADR_SIZE		54
# define DIB_HEADR_SIZE	40

#endif
