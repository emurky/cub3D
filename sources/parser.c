/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:19:10 by emurky            #+#    #+#             */
/*   Updated: 2021/04/27 07:18:36 by emurky           ###   ########.fr       */
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

void	color_to_str(int *rgb, int *i, t_all *all, char **tokens)
{
	if (ft_isdigit(tokens[1][*i]))
	{
		*rgb = ft_atoi(&(tokens[1][*i]));
		while (ft_isdigit(tokens[1][*i]))
			(*i)++;
	}
	else
		leave(ERR, ERR_FC, all, tokens);
}

void	parse_floor_ceil(t_all *all, char **tokens, int fc)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	if (array_len(tokens) != 2)
		leave(ERR, ERR_INV_FC, all, tokens);
	color_to_str(&r, &i, all, tokens);
	if (tokens[1][i++] != ',')
		leave(ERR, ERR_FC, all, tokens);
	color_to_str(&g, &i, all, tokens);
	if (tokens[1][i++] != ',')
		leave(ERR, ERR_FC, all, tokens);
	color_to_str(&b, &i, all, tokens);
	if (i != (int)ft_strlen(tokens[1]))
		leave(ERR, ERR_FC, all, tokens);
	if (!(0 <= r && r <= 255) || !(0 <= g && g <= 255) || !(0 <= b && b <= 255))
		leave(ERR, ERR_FC_RNG, all, tokens);
	init_floor_ceil(all, tokens, fc, create_rgb(r, g, b));
	all->identifiers++;
}

int		check_all_identifiers(int *flags)
{
	return ((flags[R] + flags[NO] + flags[SO] + flags[WE] + flags[EA]
			+ flags[S] + flags[F] + flags[C]) < 8);
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
		parse_identifiers(all, tokens);
	else if (str_isspace(line))
		leave(ERR, ERR_LINE, all, tokens);
}

void	make_map(t_all *all, t_list **head, int size)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = *head;
	all->map = ft_calloc(size + 1, sizeof(char *));
	if (!all->map)
		leave(ERR, ERR_MALLOC, all, NULL);
	while (temp)
	{
		all->map[i++] = ft_strdup(temp->content);
		temp = temp->next;
	}
	ft_lstclear(head);
	i = 0;
	while (all->map[i])
		ft_putendl(all->map[i++]);
}

int		is_interior(char c)
{
	return (c == '0' || c == '2'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

int		check_map_line(t_all *all, char *line)
{
	char	*head;
	char	*last_wall;

	head = line;
	if (!(*line))
	{
		if (!all->flags[EOM])
			all->flags[EOM] = TRUE;
		return (0);
	}
	while (*line)
	{
		if (!(is_interior(*line) || *line == '1' || *line == ' '))
			return (-1);
		line++;
	}
	last_wall = ft_strrchr(head, '1');
	if (last_wall)
		if (last_wall - head + 1 > all->max_map.x)
			all->max_map.x = last_wall - head + 1;
	return (1);
}

void	parse_map(t_all *all, int fd, int line_read)
{
	t_list	*head;

	head = NULL;
	while (line_read && !ft_strncmp(all->line, "", 1))
	{
		free(all->line);
		all->line = NULL;
		line_read = get_next_line(fd, &all->line);
	}
	while (line_read)
	{
		if (all->flags[EOM] && line_read && *all->line)
			leave(ERR, ERR_MAP_LST, all, NULL);
		if (check_map_line(all, all->line) > 0)
			ft_lstadd_back(&head, (ft_lstnew(ft_strdup(all->line))));
		else if (check_map_line(all, all->line) < 0)
			leave(ERR, ERR_MAP_CHR, all, NULL);
		free(all->line);
		all->line = NULL;
		line_read = get_next_line(fd, &all->line);
	}
	all->max_map.y = ft_lstsize(head);
	make_map(all, &head, all->max_map.y);
	// printf("%d max width %d max height\n", all->max_map.x, all->max_map.y);
}

void	parser(t_all *all, char *file_cub)
{
	int		fd;
	int		line_read;

	fd = open(file_cub, O_RDONLY);
	if (fd < 0)
		print_error_exit("Can't open .cub file\n");
	line_read = get_next_line(fd, &all->line);
	if (!line_read)
		leave(ERR, ERR_EMPTY, all, NULL);
	while (line_read && all->identifiers < 8)
	{
		parse_line(all, all->line);
		free(all->line);
		all->line = NULL;
		line_read = get_next_line(fd, &all->line);
	}
	if (check_all_identifiers(all->flags))
		leave(ERR, ERR_INV, all, NULL);
	parse_map(all, fd, line_read);
	close(fd);
}
