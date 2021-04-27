/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 04:44:52 by emurky            #+#    #+#             */
/*   Updated: 2021/04/27 22:33:08 by emurky           ###   ########.fr       */
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
# define ERR_TEX_EXT		"Invalid texture extension (must be .xpm)\n"
# define ERR_TEX_FD			"Incorrect path to the texture\n"
# define ERR_INV_FC			"Invalid color argument\n"
# define ERR_FC				"Wrong color format\n"
# define ERR_FC_RNG			"R G B must be in range from 0 to 255\n"
# define ERR_NL				"Should be no characters on empty line(s)\n"
# define ERR_LINE			"Incorrect identifier line\n"
# define ERR_SPCS			"Spaces on empty line\n"
# define ERR_DBL			"One of identifiers is doubled\n"
# define ERR_EMPTY			".cub file is empty\n"
# define ERR_INV			"Invalid file .cub configuration\n"
# define ERR_MAP_LST		"Map cannot be separated by empty lines\n"
# define ERR_MAP_CHR		"Invalid chars in the map\n"
# define ERR_MAP_CLSD		"Map must be closed/surrounded by walls\n"
# define ERR_PLR_DBL		"Only one player could exist on the map\n"
# define ERR_PLR_NON		"No player on the map\n"

#endif
