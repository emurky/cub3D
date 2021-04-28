/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:15:01 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 07:08:08 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	skip_spaces(int *i, t_all *all)
{
	while (all->line[*i] == ' ')
		(*i)++;
}

int	array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	str_isnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	str_isspace(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	isvalid_extension(char *file, const char *ext)
{
	int		ext_len;
	int		file_len;

	ext_len = ft_strlen(ext);
	file_len = ft_strlen(file);
	if (ft_strncmp(file + file_len - ext_len, ext, ext_len + 1))
		return (FALSE);
	return (TRUE);
}
