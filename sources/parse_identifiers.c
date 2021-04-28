/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:53:24 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 10:34:29 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_resolution(t_all *all, char **tokens)
{
	int		width;
	int		height;

	if (!all->flags[R])
	{
		if (array_len(tokens) != 3)
			leave(ERR, ERR_NUM_RES_IDS, all, tokens);
		if (!str_isnum(tokens[1]) || !str_isnum(tokens[2]))
			leave(ERR, ERR_INV_RES_ARG, all, tokens);
		width = ft_atoi(tokens[1]);
		height = ft_atoi(tokens[2]);
		if (width <= 0 || height <= 0)
			leave(ERR, ERR_INV_RES, all, tokens);
		set_screen_size(all, tokens, width, height);
		all->identifiers++;
		all->flags[R] = TRUE;
	}
	else
		leave(ERR, ERR_DBL, all, tokens);
}

void	parse_texture(t_all *all, char **tokens, int dir)
{
	int		fd;

	if (array_len(tokens) != 2)
		leave(ERR, ERR_NUM_TEX, all, tokens);
	if (!isvalid_extension(tokens[1], ".xpm"))
		leave(ERR, ERR_TEX_EXT, all, tokens);
	fd = open(tokens[1], O_RDWR);
	if (fd < 0)
		leave(ERR, ERR_TEX_FD, all, tokens);
	close(fd);
	if (dir == NO && !all->flags[NO])
		set_nswes(&all->nswes.no, &all->flags[NO], tokens[1]);
	else if (dir == SO && !all->flags[SO])
		set_nswes(&all->nswes.so, &all->flags[SO], tokens[1]);
	else if (dir == WE && !all->flags[WE])
		set_nswes(&all->nswes.we, &all->flags[WE], tokens[1]);
	else if (dir == EA && !all->flags[EA])
		set_nswes(&all->nswes.ea, &all->flags[EA], tokens[1]);
	else if (dir == S && !all->flags[S])
		set_nswes(&all->nswes.s, &all->flags[S], tokens[1]);
	else
		leave(ERR, ERR_DBL, all, tokens);
	all->identifiers++;
}

void	check_and_skip_digits(int *rgb, int *i, t_all *all, char **tokens)
{
	if (!ft_isdigit(all->line[*i]))
		leave(ERR, ERR_FC, all, tokens);
	*rgb = ft_atoi(&all->line[*i]);
	while (ft_isdigit(all->line[*i]))
		(*i)++;
}

void	check_and_skip_spaces_and_comma(int *i, t_all *all, char **tokens)
{
	if (all->line[*i] != ' ' && all->line[*i] != ',')
		leave(ERR, ERR_FC, all, tokens);
	while (all->line[*i] == ' ')
		(*i)++;
	if (all->line[(*i)++] != ',')
		leave(ERR, ERR_FC, all, tokens);
	while (all->line[*i] == ' ')
		(*i)++;
}

void	parse_floor_ceil(t_all *all, char **tokens, int fc)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	skip_spaces(&i, all);
	if (all->line[i] != 'F' && all->line[i] != 'C')
		leave(ERR, ERR_FC, all, tokens);
	i++;
	skip_spaces(&i, all);
	check_and_skip_digits(&r, &i, all, tokens);
	check_and_skip_spaces_and_comma(&i, all, tokens);
	check_and_skip_digits(&g, &i, all, tokens);
	check_and_skip_spaces_and_comma(&i, all, tokens);
	check_and_skip_digits(&b, &i, all, tokens);
	if (all->line[i] != ' ' && all->line[i])
		leave(ERR, ERR_FC, all, tokens);
	skip_spaces(&i, all);
	if (all->line[i])
		leave(ERR, ERR_FC, all, tokens);
	if (!(0 <= r && r <= 255) || !(0 <= g && g <= 255) || !(0 <= b && b <= 255))
		leave(ERR, ERR_FC_RNG, all, tokens);
	set_floor_ceil(all, tokens, fc, create_rgb(r, g, b));
	all->identifiers++;
}
