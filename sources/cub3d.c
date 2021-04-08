/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/08 03:42:26 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define SCRN_W		1200
#define SCRN_H		900

#define MAP_OFFS_X	42
#define MAP_OFFS_Y	84

#define SCALE		30

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		is_player_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
	map[2]	= ft_strdup("        1011000001110000002000001");
	map[3]	= ft_strdup("        1001000000000000000000001");
	map[4]	= ft_strdup("111111111011000001110000000000001");
	map[5]	= ft_strdup("100000000011000001110111110111111");
	map[6]	= ft_strdup("11110111111111011100000010001    ");
	map[7]	= ft_strdup("11110111111111011101010010001    ");
	map[8]	= ft_strdup("11000000110101011100000010001    ");
	map[9]	= ft_strdup("10002000000000001100000010001    ");
	map[10]	= ft_strdup("10000000000000001101010010001    ");
	map[11]	= ft_strdup("11000001110101011111011110N0111  ");
	map[12]	= ft_strdup("11110111 1110101 101111010001    ");
	map[13]	= ft_strdup("11111111 1111111 111111111111    ");
	map[14]	= NULL;
	return (map);
}

void	draw_rectangle(t_img *img, int width, int height)
{
	int		i;
	int		j;

	i = MAP_OFFS_X;
	j = MAP_OFFS_Y;
	while (j <= height + MAP_OFFS_Y)
	{
		i = MAP_OFFS_X;
		while (i <= width + MAP_OFFS_X)
		{
			my_mlx_pixel_put(img, i, j, 0x00FFFFFF);
			i++;
		}
		j++;
	}
}

void	draw_square(t_img *img, int width, t_pnt pos, int color)
{
	int		i;
	int		j;

	j = pos.y;
	while (j < width + pos.y)
	{
		i = pos.x;
		while (i < width + pos.x)
		{
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_map(t_all *all)
{
	int		i;
	int		j;
	t_pnt	pos;

	i = 0;
	pos.y = MAP_OFFS_Y;
	while (all->map[i])
	{
		j = 0;
		pos.x = MAP_OFFS_X;
		while (all->map[i][j])
		{
			draw_square(&all->img, SCALE, pos, DARK_GREY);
			if (all->map[i][j] == '1')
				draw_square(&all->img, SCALE, pos, WHITE);
			if (is_player_dir(all->map[i][j]))
				draw_square(&all->img, SCALE, pos, RED);
			pos.x += SCALE;
			j++;
		}
		pos.y += SCALE;
		i++;
	}
}

int		scaled_down_x(double index)
{
	return ((index - MAP_OFFS_X) / SCALE);
}

int		scaled_down_y(double index)
{
	return ((index - MAP_OFFS_Y) / SCALE);
}

void	cast_rays(t_all *all, int raycount)
{
	t_plr	ray;
	double	start;
	double	end;

	ray = all->plr;
	start = ray.dir - M_PI_4;
	end = ray.dir + M_PI_4;
	
	while (start <= end)
	{
		ray.x = all->plr.x;
		ray.y = all->plr.y;
		while (all->map[scaled_down_y(ray.y)][scaled_down_x(ray.x)] != '1')
		{
			ray.x += cos(start);
			ray.y -= sin(start);
			my_mlx_pixel_put(&all->img, ray.x, ray.y, BLUE);
		}
		start += M_PI_2 / raycount;
	}
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
	all.plr.y = 11.0 * SCALE + MAP_OFFS_Y;
	all.plr.dir = M_PI_2;

	draw_map(&all);

	cast_rays(&all, 100);

	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_string_put(all.mlx, all.win, 300, 300, RED, TEST);
	mlx_loop(all.mlx);
	
	return (0);
}
