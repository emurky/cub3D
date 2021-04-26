/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:19:10 by emurky            #+#    #+#             */
/*   Updated: 2021/04/26 18:16:22 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_screen_size(t_all *all, char **tokens, int width, int height)
{
	if (all->save == TRUE)
	{
		if (width > 16384 || height > 16384)
			leave(ERR, ERR_SCRNSH, all, tokens);
		else
			all->screen = (t_pnt){width, height};
	}
	else
	{
		mlx_get_screen_size(&all->screen.x, &all->screen.y);
		if (width < all->screen.x)
			all->screen.x = width;
		if (height < all->screen.y)
			all->screen.y = height;
	}
}

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
	fd = open(tokens[1], O_RDONLY);
	if (fd < 0)
		leave(ERR, ERR_TEX_FD, all, tokens);
	close(fd);
	if (dir == NO && !all->flags[NO])
		set_nswes(&all->nswes.no, all->flags[NO], tokens[1]);
	else if (dir == SO && !all->flags[SO])
		set_nswes(&all->nswes.so, all->flags[SO], tokens[1]);
	else if (dir == WE && !all->flags[WE])
		set_nswes(&all->nswes.we, all->flags[WE], tokens[1]);
	else if (dir == EA && !all->flags[EA])
		set_nswes(&all->nswes.ea, all->flags[EA], tokens[1]);
	else if (dir == S && !all->flags[S])
		set_nswes(&all->nswes.s, all->flags[S], tokens[1]);
	else
		leave(ERR, ERR_DBL, all, tokens);
	all->identifiers++;
}

void	init_floor_ceil(t_all *all, char **tokens, int fc, int color)
{
	if (fc == F && !all->flags[F])
	{
		all->floor_ceil.x = color;
		all->flags[F] = TRUE;
	}
	else if (fc == C && !all->flags[C])
	{
		all->floor_ceil.y = color;
		all->flags[C] = TRUE;
	}
	else
		leave(ERR, ERR_DBL, all, tokens);
}

void	parse_floor_ceil(t_all *all, char **tokens, int fc)
{
	int		r;
	int		g;
	int		b;
	size_t	i;

	i = 0;
	if (array_len(tokens) != 2)
		leave(ERR, ERR_INV_FC, all, tokens);
	r = ft_atoi(&(tokens[1][i]));
	i += ft_nbrlen(r);
	if (tokens[1][i++] != ',')
		leave(ERR, ERR_FC, all, tokens);
	g = ft_atoi(&(tokens[1][i]));
	i += ft_nbrlen(g);
	if (tokens[1][i++] != ',')
		leave(ERR, ERR_FC, all, tokens);
	b = ft_atoi(&(tokens[1][i]));
	i += ft_nbrlen(b);
	if (i != ft_strlen(tokens[1]))
		leave(ERR, ERR_FC, all, tokens);
	if (!(0 <= r && r <= 255) || !(0 <= g && g <= 255) || !(0 <= b && b <= 255))
		leave(ERR, ERR_FC_RNG, all, tokens);
	init_floor_ceil(all, tokens, fc, create_rgb(r, g, b));
	all->identifiers++;
	// printf("%d r %d g %d b %zu i\n", r, g ,b, i);
}

void	parse_identifiers(t_all *all, char **tokens)
{
	if (!ft_strncmp(tokens[0], "R", 2))
		parse_resolution(all, tokens);
	else if (!ft_strncmp(tokens[0], "NO", 3))
		parse_texture(all, tokens, NO);
	else if (!ft_strncmp(tokens[0], "SO", 3))
		parse_texture(all, tokens, SO);
	else if (!ft_strncmp(tokens[0], "WE", 3))
		parse_texture(all, tokens, WE);
	else if (!ft_strncmp(tokens[0], "EA", 3))
		parse_texture(all, tokens, EA);
	else if (!ft_strncmp(tokens[0], "S", 2))
		parse_texture(all, tokens, S);
	else if (!ft_strncmp(tokens[0], "F", 2))
		parse_floor_ceil(all, tokens, F);
	else if (!ft_strncmp(tokens[0], "C", 2))
		parse_floor_ceil(all, tokens, C);
	else if (tokens[0])
		leave(ERR, ERR_LINE, all, tokens);
	free_array(tokens);
}

void	parse_line(t_all *all, char *line)
{
	char	**tokens;

	if (line[0] == '\0')
		return ;
	tokens = NULL;
	tokens = ft_split(line, ' ');
	if (tokens[0])
	{
		parse_identifiers(all, tokens);
	}
	else if (str_isspace(line))
		leave(ERR, ERR_LINE, all, tokens);
}

void	parser(t_all *all, char *file_cub)
{
	int		fd;
	char	*line;
	int		line_read;

	fd = open(file_cub, O_RDONLY);
	if (fd < 0)
		print_error_exit("Can't open .cub file\n");
	line_read = get_next_line(fd, &line);
	if (!line_read)
		leave(ERR, ERR_EMPTY, all, NULL);
	while (line_read && all->identifiers < 8)
	{
		// printf("%s\n", line);
		parse_line(all, line);
		free(line);
		// all->identifiers++;
		line_read = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
}
