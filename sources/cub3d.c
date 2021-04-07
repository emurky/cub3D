/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/07 20:22:23 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define SCRN_H	800
#define SCRN_W	600
#define SCALE	20

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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

void	draw_rectangle(t_img *img, int width, int height, t_point pos)
{
	int		i;
	int		j;

	i = pos.x;
	j = pos.y;
	while (j <= height + pos.y)
	{
		i = pos.x;
		while (i <= width + pos.x)
		{
			my_mlx_pixel_put(img, i, j, 0x00FFFFFF);
			i++;
		}
		j++;
	}
}

void	draw_square(t_img *img, int width, t_point pos, int color)
{
	int		i;
	int		j;

	i = pos.x;
	j = pos.y;
	while (j <= width + pos.y)
	{
		i = pos.x;
		while (i <= width + pos.x)
		{
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_map(t_img *img, t_point pos, char **map)
{
	int		i;
	int		j;
	int		reset_posx;

	i = 0;
	reset_posx = pos.x;
	while (map[i])
	{
		j = 0;
		pos.x = reset_posx;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(img, SCALE, pos, 0x00FFFFFF);
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				draw_square(img, SCALE, pos, 0x00FF0000);
			pos.x += SCALE + 1;
			j++;
		}
		pos.y += SCALE + 1;
		i++;
	}
}

int		main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	char	**map;
	char	**head;
	// int		i = 0;
	// int		j = 0;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, SCRN_H, SCRN_W);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);
	mlx_win = mlx_new_window(mlx, SCRN_H, SCRN_W, "cub3d");

	int color = 0x00FF0000;

	map = map_init();

	t_point	pos;
	pos.x = 50;
	pos.y = 50;
	

	draw_map(&img, pos, map);
	// draw_square(&img, 100, pos, 0x00FFFFFF);

	// while (*map)
	// 	printf("%s\n", *map++);

	head = map;
	while (*map)
		free(*map++);
	free(head);


	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_string_put(mlx, mlx_win, 300, 300, color, TEST);
	mlx_loop(mlx);
	
	return (0);
}
