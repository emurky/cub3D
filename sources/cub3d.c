/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 02:51:30 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	structure_init(t_all *all)
{
	int		i;

	i = 0;
	while (i < 8)
		all->keys[i++] = 0;
	i = 0;
	while (i < 5)
		all->tex[i++].img = NULL;
	i = 0;
	while (i < 13)
		all->flags[i++] = FALSE;
	all->save = 0;
	all->identifiers = 0;
	all->frames = 1;
	all->time = 0;
	all->map = NULL;
	all->line = NULL;
	all->mlx = NULL;
	all->img.img = NULL;
	all->win = NULL;
	all->ray.z_buff = NULL;
	all->ray.sprites = NULL;
	all->nswes = (t_pths){NULL, NULL, NULL, NULL, NULL};
	all->max_map = (t_pnt){0, 0};
}

void	frame_init(t_all *all)
{
	is_enough_space_for_map(all);
	textures_init(all);
	sprites_counting(all);
	all->plr_init_pos = (t_pnt){all->ray.pos_x, all->ray.pos_y};
	all->plr_init_dir = all->plr.dir;
	all->ray.k = 1.0 / (4.0 / 3.0
			* (double)all->screen.y / (double)all->screen.x * FOV / (M_PI / 3));
	raycaster(all, &all->ray);
	if (all->flags[ISMAP_OK])
		draw_map(all);
}

int	renderer(t_all *all)
{
	mlx_clear_window(all->mlx, all->win);
	keys_handler(all);
	raycaster(all, &all->ray);
	if (all->flags[ISMAP_OK])
		draw_map(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

void	hooks_and_loops(t_all *all)
{
	mlx_hook(all->win, 2, 1L <<0, key_pressed, all);
	mlx_hook(all->win, 3, 1L <<1, key_released, all);
	mlx_hook(all->win, 17, 1L <<5, close_window, all);
	mlx_loop_hook(all->mlx, renderer, all);
	mlx_loop(all->mlx);
}

int	main(int argc, char **argv)
{
	t_all	all;

	structure_init(&all);
	if (argc !=2 && argc != 3)
		print_error_exit("Wrong number of arguments\n");
	if (!isvalid_extension(argv[1], ".cub"))
		print_error_exit("Invalid map extension\n");
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		all.save = TRUE;
	else if (argv[2])
		print_error_exit("Wrong second argument\n");
	parser(&all, argv[1]);
	mlx_start(&all);
	frame_init(&all);
	if (all.save)
		save_screenshot(&all);
	hooks_and_loops(&all);
	return (0);
}
