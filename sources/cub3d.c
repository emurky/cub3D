/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/09 04:44:16 by emurky           ###   ########.fr       */
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

	// // draw_rectangle(&all.img, 500, 500, 0xFFFF0000);

	// int i = 0;
	// int j;
	// while (i < 500)
	// {
	// 	j = 0;
	// 	while (j < 500)
	// 	{
	// 		mlx_pixel_put(all.mlx, all.win, i, j, 0x88FF0000);
	// 		j++;
	// 	}
	// 	i++;
	// }
	
	printf("%X\n", get_t(0x88FF0000));
	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_string_put(all.mlx, all.win, 300, 300, RED, TEST);
	

	mlx_loop(all.mlx);
	
	return (0);
}
