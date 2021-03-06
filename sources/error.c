/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:24:43 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 03:02:47 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_array(char **array)
{
	int		i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	free_malloc_pointers(t_all *all)
{
	if (all->line)
		free(all->line);
	if (all->ray.z_buff)
		free(all->ray.z_buff);
	if (all->ray.sprites)
		free(all->ray.sprites);
	if (all->nswes.no)
		free(all->nswes.no);
	if (all->nswes.so)
		free(all->nswes.so);
	if (all->nswes.we)
		free(all->nswes.we);
	if (all->nswes.ea)
		free(all->nswes.ea);
	if (all->nswes.s)
		free(all->nswes.s);
	printf("Allocated memory were freed\n");
}

void	clean_all(t_all *all)
{
	free_array(all->map);
	printf("Map was freed\n");
	clean_mlx(all);
	free_malloc_pointers(all);
}

void	print_error_exit(char *err_str)
{
	write(2, "Error\n", 6);
	write(2, err_str, ft_strlen(err_str));
	exit(EXIT_FAILURE);
}

void	leave(int error, char *err_str, t_all *all, char **array)
{
	if (array)
		free_array(array);
	if (error)
	{
		write(2, "Error\n", 6);
		write(2, err_str, ft_strlen(err_str));
		clean_all(all);
		write(2, "Exiting cub3D...\n", 17);
		exit(EXIT_FAILURE);
	}
	clean_all(all);
	printf("Bye-bye\n");
	exit(EXIT_SUCCESS);
}
