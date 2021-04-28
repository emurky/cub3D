/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:57:53 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 02:58:59 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_interior(char c)
{
	return (c == '0' || c == '2'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

int	check_neighbours(t_map map, int row, int col)
{
	if (row == 0 || row == map.height - 1 || col == 0 || col == map.width - 1
		|| map.map[row - 1][col - 1] == ' ' || map.map[row - 1][col] == ' '
		|| map.map[row - 1][col + 1] == ' ' || map.map[row][col - 1] == ' '
		|| map.map[row][col + 1] == ' '
		|| map.map[row + 1][col - 1] == ' ' || map.map[row + 1][col] == ' '
		|| map.map[row + 1][col + 1] == ' ')
		return (FALSE);
	return (TRUE);
}

int	check_continuity(t_map map)
{
	int		i;
	int		j;

	j = 0;
	while (j < map.height)
	{
		i = 0;
		while (i < map.width)
		{
			if (is_interior(map.map[j][i]) && !check_neighbours(map, j, i))
				return (FALSE);
			i++;
		}
		j++;
	}
	return (TRUE);
}

int	check_map_line(t_all *all, char *line)
{
	char	*head;
	int		line_len;

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
	line_len = ft_strlen(head);
	if (line_len > all->max_map.x)
		all->max_map.x = line_len;
	return (1);
}
