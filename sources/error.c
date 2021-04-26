/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:24:43 by emurky            #+#    #+#             */
/*   Updated: 2021/04/26 03:26:24 by emurky           ###   ########.fr       */
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

void	free_array(char **array)
{
	int		i;

	i = 0;
	if (array)
	{
		while (array[i])
			free(array[i++]);
		free(array);
		array = NULL;
	}
}

void	free_malloc_pointers(t_all *all)
{
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

// void	free_malloc_pointers(t_all *all)
// {
// 	if (all->ray.z_buff)
// 	{
// 		free(all->ray.z_buff);
// 		all->ray.z_buff == NULL;
// 	}
// 	if (all->ray.sprites)
// 	{
// 		free(all->ray.sprites);
// 		all->ray.sprites = NULL;
// 	}
// 	if (all->nswes.no)
// 	{
// 		free(all->nswes.no);
// 		all->nswes.no = NULL;
// 	}
// 	if (all->nswes.so)
// 	{
// 		free(all->nswes.so);
// 		all->nswes.so = NULL;
// 	}
// 	if (all->nswes.we)
// 		free(all->nswes.no);
// 		all->nswes.we = NULL;
// 	}
// 	if (all->nswes.ea)
// 		free(all->nswes.ea);
// 	if (all->nswes.s)
// 		free(all->nswes.s);
// 	printf("Allocated memory were freed\n");
// }

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
		// clean_map(all->map);
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
		exit(EXIT_FAILURE);
	}
	clean_all(all);
	printf("Bye-bye\n");
	exit(EXIT_SUCCESS);
}
