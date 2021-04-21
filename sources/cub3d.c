/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/21 16:36:22 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

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
	map[1]	= ft_strdup("        1000000000110000000000001");
	map[2]	= ft_strdup("        1011000001110002000000201");
	map[3]	= ft_strdup("        1001020000000000000000001");
	map[4]	= ft_strdup("111111111011000001110000000000001");
	map[5]	= ft_strdup("100000000011000001110111110111111");
	map[6]	= ft_strdup("11110111111111011100000010001    ");
	map[7]	= ft_strdup("11110111111111011101010010001    ");
	map[8]	= ft_strdup("11000000110101011100000010001    ");
	map[9]	= ft_strdup("10002000000000000000000000001    ");
	map[10]	= ft_strdup("10000000000000001101010010001    ");
	map[11]	= ft_strdup("11000001110101011111011110N0111  ");
	map[12]	= ft_strdup("11110111 1110101 101111010001    ");
	map[13]	= ft_strdup("11111111 1111111 111111111111    ");
	map[14]	= NULL;
	return (map);
}

void	clean_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	printf("Map was freed properly\n");
}

void	clean_win(t_img *img)
{
	int		i;
	int		j;

	i = 0;
	// j = 0;
	while (i < SCRN_W)
	{
		j = 0;
		while (j < SCRN_H)
		{
			my_mlx_pixel_put(img, i, j, BLACK);
			j++;
		}
		i++;
	}
}

int		renderer(int key, t_all *all)
{
	char *counter;

	counter = ft_itoa(all->frames_counter);
	mlx_clear_window(all->mlx, all->win);
	clean_win(&all->img);
	key_press(key, all);
	raycaster(all, &all->ray);
	draw_player(all);
	all->frames_counter++;
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	mlx_string_put(all->mlx, all->win, 1150, 15, BLACK, counter);
	free(counter);
	return (0);
}

int		main(void)
{
	t_all	all;

	all.mlx = mlx_init();
	all.img.img = mlx_new_image(all.mlx, SCRN_W, SCRN_H);
	all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bpp,
										&all.img.linelen, &all.img.endian);
	all.win = mlx_new_window(all.mlx, SCRN_W, SCRN_H, "cub3d");

	all.map = map_init();

	all.frames_counter = 1;
	set_player_pos(&all, 27, 11);
	printf("%f posx %f posy\n", all.ray.pos_x, all.ray.pos_y);
	set_player_dir(&all, M_PI_2);

	// all.plr_init.x = 27;
	// all.plr_init.y = 11;
	// all.plr_init.dir = M_PI;

	raycaster(&all, &all.ray);
	draw_player(&all);
	
	// mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	// mlx_string_put(all.mlx, all.win, 300, 300, RED, TEST);
	// mlx_key_hook(all.win, esc_exit, &all);
	// mlx_key_hook(all.win, print_key, &all);
	// mlx_key_hook(all.win, key_press, &all);
	// mlx_key_hook(all.win, esc_exit, &all);
	
	t_pnt screen;
	
	// double scale;
	mlx_get_screen_size(&screen.x, &screen.y);
	printf("%d width, %d height\n", screen.x, screen.y);

	// clean_win(&all.img);
	// draw_square(&all.img, 300, (t_pnt){0, 0}, BLACK);
	// mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_hook(all.win, 2, 1L<<0, renderer, &all);
	mlx_hook(all.win, 17, 1L<<5, close_window, &all);
	mlx_loop(all.mlx);
	return (0);
}
