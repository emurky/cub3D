/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 00:55:55 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 01:32:52 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	intset_little_endian(char *dest, uint32_t n, int size)
{
	while (size--)
	{
		*dest++ = (unsigned char)n;
		n >>= 8;
	}
}

void	write_headers(t_all *all, int fd)
{
	char		header[HEADR_SIZE];
	uint32_t	size;

	size = all->screen.x * all->img.bpp >> 3;
	size = (size + 3) >> 2 << 2;
	ft_bzero(header, HEADR_SIZE);
	ft_memcpy(header, "BM", 2);
	intset_little_endian(header + 2, size, 4);
	intset_little_endian(header + 10, HEADR_SIZE, 4);
	intset_little_endian(header + 14, DIB_HEADR_SIZE, 4);
	intset_little_endian(header + 18, all->screen.x, 4);
	intset_little_endian(header + 22, all->screen.y, 4);
	intset_little_endian(header + 26, 1, 2);
	intset_little_endian(header + 28, all->img.bpp, 2);
	write(fd, header, HEADR_SIZE);
}

void	write_pixel_data(t_all *all, int fd)
{
	int	i;
	int	padding;

	padding = 4 - ((all->screen.x * all->img.bpp >> 3) | 0x3);
	i = all->screen.y - 1;
	while (i >= 0)
	{
		write(fd, all->img.addr + (i * all->screen.x
				* all->img.bpp >> 3), all->img.linelen);
		write(fd, "\0\0\0", padding);
		i--;
	}
}

void	save_screenshot(t_all *all)
{
	int	fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (!fd)
		leave(ERR, ERR_SCRNSH, all, NULL);
	write_headers(all, fd);
	write_pixel_data(all, fd);
	close(fd);
	printf("%s\n", "Screenshot was saved successfully");
	leave(NO_ERR, NULL, all, NULL);
}
