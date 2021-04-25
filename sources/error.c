/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:24:43 by emurky            #+#    #+#             */
/*   Updated: 2021/04/25 05:20:15 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	map = NULL;
	printf("Map was freed\n");
}

void	free_malloc_pointers(t_all *all)
{
	if (all->ray.z_buff)
		free(all->ray.z_buff);
	if (all->ray.sprites)
		free(all->ray.sprites);
	printf("Allocated memory were freed\n");
}

void	clean_mlx(t_all *all)
{
	int		i;

	i = 0;
	if (all->mlx && all->win)
		mlx_destroy_window(all->mlx, all->win);
	if (all->mlx && all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	while (i < 5)
	{
		if (all->mlx && all->tex[i].img)
			mlx_destroy_image(all->mlx, all->tex[i].img);
		i++;
	}
	printf("MiniLibX items were freed\n");
}

void	clean_all(t_all *all)
{
		clean_map(all->map);
		free_malloc_pointers(all);
		clean_mlx(all);
}

void	print_error_exit(char *err_str)
{
	write(2, "Error\n", 6);
	write(2, err_str, ft_strlen(err_str));
	exit(EXIT_FAILURE);
}

void	leave(int error, char *err_str, t_all *all)
{
	if (error)
	{
		write(2, "Error\n", 6);
		write(2, err_str, ft_strlen(err_str));
		clean_all(all);
		exit(EXIT_FAILURE);
	}
	clean_all(all);;
	printf("Bye-bye\n");
	exit(EXIT_SUCCESS);
}
