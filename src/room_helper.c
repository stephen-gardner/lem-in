/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:32:19 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/21 23:21:06 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

t_room	*build_room(char **params)
{
	t_room	*room;

	if (!(room = ft_memalloc(sizeof(t_room))))
		DEFAULT_ERROR;
	room->name = params[0];
	if (!set_pos(params[1], &room->pos_x) || !set_pos(params[2], &room->pos_y))
	{
		free(room);
		return (NULL);
	}
	return (room);
}

t_room	*find_room(t_room **rooms, int size, char *name)
{
	t_room	*room;
	int		i;

	i = 0;
	while (i < size)
	{
		room = rooms[i++];
		if (!ft_strcmp(name, room->name))
			return (room);
	}
	return (NULL);
}

void	add_link(t_room *dst, t_room *to_add)
{
	t_room	**tmp;

	if (find_room(dst->links, dst->num_links, to_add->name))
		return ;
	tmp = dst->links;
	if (!(dst->links = ft_memalloc(sizeof(t_room) * (dst->num_links + 1))))
		DEFAULT_ERROR;
	ft_memcpy(dst->links, tmp, sizeof(t_room) * dst->num_links);
	dst->links[dst->num_links++] = to_add;
	free(tmp);
}
