/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:58:22 by emurky            #+#    #+#             */
/*   Updated: 2021/04/06 04:47:23 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_free_line(char *s1, char *s2)
{
	char	*joined_str;
	char	*s1_ptr;
	size_t	len;

	if (!(s1 && s2))
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc(sizeof(char) * (len + 1));
	if (!joined_str)
		return (NULL);
	joined_str[len] = '\0';
	s1_ptr = s1;
	while (*s1_ptr)
		*joined_str++ = *s1_ptr++;
	while (*s2)
		*joined_str++ = *s2++;
	free(s1);
	s1 = NULL;
	return (joined_str - len);
}

static int	nl_finder(char **buffer, char **line)
{
	char	*nl_ptr;

	nl_ptr = ft_strchr(*buffer, '\n');
	if (nl_ptr)
	{
		*nl_ptr++ = '\0';
		*line = ft_strjoin_free_line(*line, *buffer);
		ft_memmove(*buffer, nl_ptr, BUFFER_SIZE - (nl_ptr - *buffer) + 1);
		return (1);
	}
	*line = ft_strjoin_free_line(*line, *buffer);
	return (0);
}

static int	lines_reading(char **buffer, int fd, int *read_count, char **line)
{
	*read_count = read(fd, *buffer, BUFFER_SIZE);
	while (*read_count)
	{
		if (*read_count < 0)
			return (-1);
		(*buffer)[*read_count] = '\0';
		if (nl_finder(buffer, line))
			return (1);
		*read_count = read(fd, *buffer, BUFFER_SIZE);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*buffer;
	int				read_count;
	int				reading_status;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup("");
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (-1);
	}
	else if (nl_finder(&buffer, line))
		return (1);
	reading_status = lines_reading(&buffer, fd, &read_count, line);
	if (reading_status == -1)
		return (-1);
	else if (reading_status == 1)
		return (1);
	free(buffer);
	buffer = NULL;
	return (0);
}
