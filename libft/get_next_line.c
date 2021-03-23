/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:58:22 by emurky            #+#    #+#             */
/*   Updated: 2021/03/23 23:41:37 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_line(char *s1, char *s2)
{
	char	*joined_str;
	char	*s1_ptr;
	size_t	len;

	if (!(s1 && s2))
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(joined_str = malloc(sizeof(char) * (len + 1))))
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

int		nl_finder(char **buffer, char **line)
{
	char	*nl_ptr;

	if ((nl_ptr = ft_strchr(*buffer, '\n')))
	{
		*nl_ptr++ = '\0';
		*line = ft_strjoin_free_line(*line, *buffer);
		ft_memmove(*buffer, nl_ptr, BUFFER_SIZE - (nl_ptr - *buffer) + 1);
		return (1);
	}
	*line = ft_strjoin_free_line(*line, *buffer);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*buffer[FDS];
	int				read_count;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup("");
	if (!(buffer[fd]))
	{
		if (!(buffer[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
	}
	else if (nl_finder(&(buffer[fd]), line))
		return (1);
	while ((read_count = read(fd, buffer[fd], BUFFER_SIZE)))
	{
		if (read_count < 0)
			return (-1);
		buffer[fd][read_count] = '\0';
		if (nl_finder(&(buffer[fd]), line))
			return (1);
	}
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (0);
}
