/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:59:30 by emurky            #+#    #+#             */
/*   Updated: 2021/04/28 03:00:20 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	malloc_map(t_all *all, t_list **head)
{
	int		j;
	t_list	*temp;

	j = 0;
	temp = *head;
	all->map = malloc((all->max_map.y + 1) * sizeof(char *));
	if (!all->map)
		leave(ERR, ERR_MALLOC, all, NULL);
	while (temp && j < all->max_map.y)
	{
		all->map[j] = NULL;
		all->map[j] = malloc((all->max_map.x + 1) * sizeof(char));
		if (!all->map[j])
			leave(ERR, ERR_MALLOC, all, NULL);
		all->map[j][all->max_map.x] = '\0';
		ft_memset(all->map[j], ' ', all->max_map.x);
		ft_memmove(all->map[j], temp->content, ft_strlen(temp->content));
		temp = temp->next;
		j++;
	}
	all->map[j] = NULL;
}

void	make_map(t_all *all, t_list **head)
{
	t_map	map;

	malloc_map(all, head);
	ft_lstclear(head);
	map = (t_map){all->map, all->max_map.x, all->max_map.y};
	set_player(all, all->map);
	if (!all->flags[PLR])
		leave(ERR, ERR_PLR_NON, all, NULL);
	if (!check_continuity(map))
		leave(ERR, ERR_MAP_CLSD, all, NULL);
}

void	get_map_line(t_all *all, t_list **head, int line_read)
{
	if (all->flags[EOM] && line_read && *all->line)
		leave(ERR, ERR_MAP_LST, all, NULL);
	if (check_map_line(all, all->line) > 0)
		ft_lstadd_back(head, (ft_lstnew(ft_strdup(all->line))));
	else if (check_map_line(all, all->line) < 0)
		leave(ERR, ERR_MAP_CHR, all, NULL);
	free(all->line);
	all->line = NULL;
}

void	parse_map(t_all *all, int fd, int line_read)
{
	t_list	*head;

	head = NULL;
	while (line_read && !ft_strncmp(all->line, "", 1))
	{
		free(all->line);
		all->line = NULL;
		line_read = get_next_line(fd, &all->line);
	}
	while (line_read)
	{
		get_map_line(all, &head, line_read);
		line_read = get_next_line(fd, &all->line);
	}
	get_map_line(all, &head, line_read);
	all->max_map.y = ft_lstsize(head);
	make_map(all, &head);
}
