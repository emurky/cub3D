/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/27 06:12:57 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**map_init(void);

void	fps(t_all *all)
{
	int		old_time;
	double	frame_time;
	char	*fps;

	fps = NULL;
	old_time = all->time;
	all->time = (double)clock();
	frame_time = (all->time - old_time) / CLOCKS_PER_SEC;
	fps = ft_itoa((int)round(1 / frame_time));
	mlx_string_put(all->mlx, all->win, all->screen.x - 50, 15, BLACK, fps);
	all->move_speed = frame_time * 4.0;
	all->rotate_speed = frame_time * 1.5;
	if (fps)
		free(fps);
}

void	is_enough_space_for_map(t_all *all, char **map)
{
	int		i;
	int		j;
	t_pnt	max;

	j = 0;
	max.x = 0;
	max.y = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			i++;
			if (max.x < i)
				max.x = i;
		}
		j++;
		if (max.y < j)
			max.y = j;
	}
	all->max_map = (t_pnt){max.x, max.y};
	printf("%d max x %d max y\n", all->max_map.x, all->max_map.y);
	max.x = max.x * SCALE + MAP_OFFS_X * 2;
	max.y = max.y * SCALE + MAP_OFFS_Y * 2;
	if (max.x < all->screen.x && max.y < all->screen.y && DRAW_MAP)
		all->flags[ISMAP_OK] = TRUE;
}

int		renderer(t_all *all)
{
	mlx_clear_window(all->mlx, all->win);
	keys_handler(all);
	raycaster(all, &all->ray);
	if (all->flags[ISMAP_OK])
		draw_map(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	fps(all);
	// frames_counter(all);
	return (0);
}

void	mlx_start(t_all *all)
{
	all->mlx = mlx_init();
	all->img.img = mlx_new_image(all->mlx, all->screen.x, all->screen.y);
	all->img.addr = mlx_get_data_addr
		(all->img.img, &all->img.bpp, &all->img.linelen, &all->img.endian);
	all->win = mlx_new_window(all->mlx, all->screen.x, all->screen.y, "cub3D");
}

void	init(t_all *all)
{
	// all->map = map_init();
	// is_enough_space_for_map(all, all->map);
	textures_init(all);
	sprites_counting(all);
	set_player_pos(all, 26, 11);
	set_player_dir(all, M_PI_2);
	all->ray.k = 1.0 / (4.0 / 3.0
			* (double)all->screen.y / (double)all->screen.x * FOV / (M_PI / 3));
	raycaster(all, &all->ray);
}

void	structure_init(t_all *all)
{
	int		i;

	i = 0;
	all->save = 0;
	all->identifiers = 0;
	all->frames = 1;
	all->time = 0;
	while (i < 8)
		all->keys[i++] = 0;
	i = 0;
	while (i < 5)
		all->tex[i++].img = NULL;
	i = 0;
	while (i < 10)
		all->flags[i++] = FALSE;
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

void	hooks_and_loops(t_all *all)
{
	mlx_hook(all->win, 2, 1L <<0, key_pressed, all);
	mlx_hook(all->win, 3, 1L <<1, key_released, all);
	mlx_hook(all->win, 17, 1L <<5, close_window, all);
	mlx_loop_hook(all->mlx, renderer, all);
	mlx_loop(all->mlx);
}

int		main(int argc, char **argv)
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
	init(&all);
	hooks_and_loops(&all);

	return (0);
}

char	**map_init(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 15);
	map[0]	= ft_strdup(" 111    1111111111111111111111111");
	map[1]	= ft_strdup(" 101    1000000000110000002000001");
	map[2]	= ft_strdup(" 111    1011000001110000200000201");
	map[3]	= ft_strdup("        1001020000000000002002001");
	map[4]	= ft_strdup("111111111011000001110000000000001");
	map[5]	= ft_strdup("100000000011000001110111110111111");
	map[6]	= ft_strdup("11110111111111011100000012221");
	map[7]	= ft_strdup("11110111111111011101010010221");
	map[8]	= ft_strdup("11000000110101011100000012201");
	map[9]	= ft_strdup("10202020200000000000000000201");
	map[10]	= ft_strdup("10000000002000001101010010001");
	map[11]	= ft_strdup("11000001110101011111011100N0011");
	map[12]	= ft_strdup("11110111 1110101 101111010001");
	map[13]	= ft_strdup("11111111 1111111 111111111111");
	map[14]	= NULL;
	return (map);
}

// char	**map_init(void)
// {
// 	char	**map;

// 	map = malloc(sizeof(char *) * 15);
// 	map[0]	= ft_strdup("111");
// 	map[1]	= ft_strdup("1N1");
// 	map[2]	= ft_strdup("111");
// 	map[3]	= NULL;
// 	return (map);
// }

// char	**map_init(void)
// {
// 	char	**map;

// 	map = malloc(sizeof(char *) * 15);
// 	map[0]	= ft_strdup("        1111111111111111111111111");
// 	map[1]	= ft_strdup("        1000000000110000002000201");
// 	map[2]	= ft_strdup("        101100000111000111000001");
// 	map[3]	= ft_strdup("        1001000000000001 1000201");
// 	map[4]	= ft_strdup("11111111101100000110000111000001");
// 	map[5]	= ft_strdup("100000000011000001110111110111111");
// 	map[6]	= ft_strdup("11110111111111011100000010001");
// 	map[7]	= ft_strdup("11110111111111011101010010001");
// 	map[8]	= ft_strdup("11000000110101011100000000001");
// 	map[9]	= ft_strdup("10000000000000000000000000001");
// 	map[10]	= ft_strdup("10000000000000001101010010001");
// 	map[11]	= ft_strdup("11000001110101011111011100N0111");
// 	map[12]	= ft_strdup("11110111 1110101 101111010001");
// 	map[13]	= ft_strdup("11111111 1111111 111111111111");
// 	map[14]	= NULL;
// 	return (map);
// }
