/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/23 03:50:45 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	gnl_test(void)
{
	char	*line;
	int		fd;

	fd = open("map.cub", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	ft_putendl("salam aleykum");
}

char	**map_init(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 15);
	map[0]	= ft_strdup("        1111111111111111111111111");
	map[1]	= ft_strdup("        1000000000110000002000001");
	map[2]	= ft_strdup("        1011000001110000200000201");
	map[3]	= ft_strdup("        1001020000000000002002001");
	map[4]	= ft_strdup("111111111011000001110000000000001");
	map[5]	= ft_strdup("100000000011000001110111110111111");
	map[6]	= ft_strdup("11110111111111011100000010001");
	map[7]	= ft_strdup("11110111111111011101010010001");
	map[8]	= ft_strdup("11000000110101011100000010001");
	map[9]	= ft_strdup("10202020200000000000000000001");
	map[10]	= ft_strdup("10000000002000001101010010001");
	map[11]	= ft_strdup("11000001110101011111011100N0111");
	map[12]	= ft_strdup("11110111 1110101 101111010001");
	map[13]	= ft_strdup("11111111 1111111 111111111111");
	map[14]	= NULL;
	return (map);
}

int		renderer(int key, t_all *all)
{
	mlx_clear_window(all->mlx, all->win);
	clean_win(all);
	key_press(key, all);
	raycaster(all, &all->ray);
	frames_counter(all);

	return (0);
}

void	mlx_start(t_all *all)
{
	all->screen.x = SCRN_W;
	all->screen.y = SCRN_H;
	all->mlx = mlx_init();
	all->img.img = mlx_new_image(all->mlx, all->screen.x, all->screen.y);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
										&all->img.linelen, &all->img.endian);
	all->win = mlx_new_window(all->mlx, all->screen.x, all->screen.y, "cub3d");
}

void	init(t_all *all)
{
	all->map = map_init();
	all->floor_ceil.x = BORDEAUX;
	all->floor_ceil.y = SKY_BLUE;
	textures_init(all);
	sprites_counting(all);
	// sprites_init(all);
	set_player_pos(all, 26, 11);
	set_player_dir(all, M_PI_2);
	all->frames = 1;
}

int		main(void)
{
	t_all	all;

	mlx_start(&all);
	init(&all);
	// printf("%f posx %f posy\n", all.ray.pos_x, all.ray.pos_y);
	
	raycaster(&all, &all.ray);

	// printf("%p in main\n", (void *)all.spr.img);
	// int color = my_mlx_pixel_get(&all.img, 600, 10);
	// printf("%X pixel color\n", color);
	// mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	// mlx_string_put(all.mlx, all.win, 300, 300, RED, TEST);
	// mlx_key_hook(all.win, esc_exit, &all);
	// mlx_key_hook(all.win, print_key, &all);
	// mlx_key_hook(all.win, key_press, &all);
	// mlx_key_hook(all.win, esc_exit, &all);
	// t_pnt screen;
	// double scale;
	// mlx_get_screen_size(&screen.x, &screen.y);
	// printf("%d width, %d height\n", screen.x, screen.y);
	// int pixel = 0;
	int pixel2 = my_mlx_pixel_get(&all.tex[4], 34, 34);
	printf("%X pixel\n", pixel2);

	mlx_hook(all.win, 2, 1L<<0, renderer, &all);
	mlx_hook(all.win, 17, 1L<<5, close_window, &all);
	mlx_loop(all.mlx);
	return (0);
}
