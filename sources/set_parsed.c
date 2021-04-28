/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parsed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:55:04 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 02:56:54 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_screen_size(t_all *all, char **tokens, int width, int height)
{
	if (all->save == TRUE)
	{
		if (width > 16384 || height > 16384)
			leave(ERR, ERR_SCRNSH_RES, all, tokens);
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

void	set_floor_ceil(t_all *all, char **tokens, int fc, int color)
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

void	init_player(t_all *all, char **map, int i, int j)
{
	if (!all->flags[PLR])
	{
		set_player_pos(all, i, j);
		if (map[j][i] == 'N')
			set_player_dir(all, M_PI_2);
		else if (map[j][i] == 'S')
			set_player_dir(all, 3 * M_PI_2);
		else if (map[j][i] == 'W')
			set_player_dir(all, M_PI);
		if (map[j][i] == 'E')
			set_player_dir(all, 0.0);
		all->flags[PLR] = TRUE;
	}
	else
		leave(ERR, ERR_PLR_DBL, all, NULL);
}

void	set_player(t_all *all, char **map)
{
	int		i;
	int		j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (is_player_dir(map[j][i]))
				init_player(all, map, i, j);
			i++;
		}
		j++;
	}
}
