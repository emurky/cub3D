/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:19:10 by emurky            #+#    #+#             */
/*   Updated: 2021/04/26 00:09:28 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int		str_isnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void	print_error_free_exit(char *err_str, char **array)
{
	free_array(array);
	print_error_exit(err_str);
}

void	parse_resolution(t_all *all, char **tokens)
{
	int		width;
	int		height;

	if (array_len(tokens) != 3)
		print_error_free_exit(ERR_NUM_RES_IDS, tokens);
	if (!str_isnum(tokens[1]) || !str_isnum(tokens[2]))
		print_error_free_exit(ERR_INV_RES_ARG, tokens);
	width = ft_atoi(tokens[1]);
	height = ft_atoi(tokens[2]);
	if (width <= 0 || height <= 0)
		// || ft_nbrlen(width) != ft_strlen(tokens[1])
		// || ft_nbrlen(height) != ft_strlen(tokens[2]))
		print_error_free_exit(ERR_INV_RES, tokens);
	if (all->save)
	{
		if (width > 16384 || height > 16384)
			print_error_free_exit(ERR_SCRNSH, tokens);
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
	all->identifiers++;
}

void	parse_line(t_all *all, char *line)
{
	char	**tokens;
// (void)all;
	tokens = NULL;
	printf("%s - line\n", line);
	tokens = ft_split(line, ' ');
	// for (int i = 0; i < 3; i++)
		printf("%s identifier\n", tokens[0]);
	if (!ft_strncmp(tokens[0], "R", 2)) {
		parse_resolution(all, tokens);}
	else
	{
		free_array(tokens);
		tokens = NULL;
		all->identifiers++;
		return ;
	}
	
}

void	parser(t_all *all, char *file_cub)
{
	int		fd;
	char	*line;
	int		line_read;

// (void)all;
	fd = open(file_cub, O_RDONLY);
	if (fd < 0)
		print_error_exit("Can't open .cub file\n");
	line_read = get_next_line(fd, &line);
	while (line_read && all->identifiers < 1)
	{
		// printf("%s\n", line);
		parse_line(all, line);
		free(line);
		// all->identifiers++;
		line_read = get_next_line(fd, &line);
	}
	free(line);
	
}
