/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/13 03:32:22 by emurky           ###   ########.fr       */
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

void	set_player_dir(t_plr *plr, double direction)
{
	plr->dir = direction;
	plr->start = direction - FOV / 2;
	plr->end = direction + FOV / 2;
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

int		print_key(int key, t_all *all)
{
	(void)all;
	printf("%d was pressed\n", key);
	return (0);
}

void	clean_map(char ***map)
{
	while (**map)
		free((**map)++);
	free(*map);
}

int		esc_exit(int key, t_all *all)
{
	(void)all;
	// mlx_destroy_window(all->mlx, all->win);
	if (key == KEY_ESC)
	{
		// clean_map(&all->map);
		exit(0);
	}
	return (0);
}

int		close_window(int button, t_all *all)
{
	(void)all;
	printf("%d was pressed\n", button);
	return (0);
}

char	map_char(t_all *all)
{
	return (all->map[scaled_down_y(all->plr.y)][scaled_down_x(all->plr.x)]);
}

int		key_press(int key, t_all *all)
{
	mlx_clear_window(all->mlx, all->win);
	// if (map_char(all) == '1')
	// {
	// 	printf("%f is x %f is y\n", all->plr.x, all->plr.y);
	// 	all->plr.dir += M_PI - 2 * all->plr.dir;
	// 	all->plr.start = all->plr.dir - FOV / 2;
	// 	all->plr.end = all->plr.dir + FOV / 2;
	// 	all->plr.x += cos(all->plr.dir) * SCALE / 4;
	// 	all->plr.y -= sin(all->plr.dir) * SCALE / 4;
	// }
	if (map_char(all) != '1')
	{
		if (key == KEY_W)
		{
			all->plr.x += cos(all->plr.dir) * MOVE_SPEED;
			all->plr.y -= sin(all->plr.dir) * MOVE_SPEED;
		}
		if (key == KEY_S)
		{
			all->plr.x -= cos(all->plr.dir) * MOVE_SPEED;
			all->plr.y += sin(all->plr.dir) * MOVE_SPEED;
		}
		if (key == KEY_A)
		{
			all->plr.x -= cos(all->plr.dir - M_PI_2) * MOVE_SPEED;
			all->plr.y += sin(all->plr.dir - M_PI_2) * MOVE_SPEED;
		}
		if (key == KEY_D)
		{
			all->plr.x -= cos(all->plr.dir + M_PI_2) * MOVE_SPEED;
			all->plr.y += sin(all->plr.dir + M_PI_2) * MOVE_SPEED;
		}
		if (key == KEY_LEFT)
		{
			all->plr.dir += ROTATE_SPEED;
			all->plr.start += ROTATE_SPEED;
			all->plr.end += ROTATE_SPEED;
		}
		if (key == KEY_RIGHT)
		{
			set_player_dir(&all->plr, all->plr.dir - ROTATE_SPEED);
		}
	}
	else
	{
		all->plr.x = 27.0 * SCALE + MAP_OFFS_X - SCALE / 2;
		all->plr.y = 11.0 * SCALE + MAP_OFFS_Y + SCALE / 2;
		set_player_dir(&all->plr, M_PI_2);
	}
	if (key == KEY_ESC)
		exit(0);
	draw_player(all);
	return (0);
}

int		render_next_frame(t_all *all)
{
	draw_map(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	mlx_destroy_image(all->mlx, all->img.img);
	mlx_key_hook(all->win, key_press, all);
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


	all.plr.x = 27.0 * SCALE + MAP_OFFS_X - SCALE / 2;
	all.plr.y = 11.0 * SCALE + MAP_OFFS_Y + SCALE / 2;
	set_player_dir(&all.plr, M_PI_2);

	draw_player(&all);
	
	// mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	// mlx_string_put(all.mlx, all.win, 300, 300, RED, TEST);
	
	// mlx_key_hook(all.win, esc_exit, &all);
	// mlx_key_hook(all.win, print_key, &all);
	// mlx_loop(all.mlx);

	// mlx_key_hook(all.win, key_press, &all);
	// mlx_key_hook(all.win, esc_exit, &all);

	// mlx_loop_hook(all.mlx, render_next_frame, &all);
	mlx_hook(all.win, 2, 1L<<0, key_press, &all);
	// mlx_hook(all.win, 2, 1L<<0, esc_exit, &all);
	mlx_loop(all.mlx);
	return (0);
}
