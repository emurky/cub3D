/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 04:44:52 by emurky            #+#    #+#             */
/*   Updated: 2021/04/26 08:29:29 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR				TRUE
# define NO_ERR				FALSE

# define ERR_MALLOC			"Memory allocation failed\n"
# define ERR_NUM_RES_IDS	"Wrong number of resolution identifiers\n"
# define ERR_INV_RES_ARG	"Invalid resolution arguments\n"
# define ERR_INV_RES		"Invalid resolution\n"
# define ERR_SCRNSH			"Resolution for screenshot is too big\n"
# define ERR_NUM_TEX		"Wrong number of texture identifiers\n"
# define ERR_TEX_EXT		"Invalid texture extension (should be .xpm)\n"
# define ERR_TEX_FD			"Can't open a texture file\n"
# define ERR_INV_FC			"Invalid color argument\n"
# define ERR_FC				"Wrong color format\n"
# define ERR_FC_RNG			"R G B must be in range from 0 to 255\n"
# define ERR_NL				"Should be no characters on empty line(s)\n"
# define ERR_LINE			"Incorrect identifier line\n"
# define ERR_DBL			"One of arguments is doubled\n"
# define ERR_EMPTY			".cub file is empty\n"

#endif
