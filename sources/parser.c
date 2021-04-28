/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:19:10 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 10:34:48 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_all_identifiers(int *flags)
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
		leave(ERR, ERR_SPCS, all, tokens);
}

void	parser(t_all *all, char *file_cub)
{
	int		fd;
	int		line_read;

	fd = open(file_cub, O_RDWR);
	if (fd < 0)
		print_error_exit("Cannot open .cub file\n");
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
