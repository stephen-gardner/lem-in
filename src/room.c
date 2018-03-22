/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:01:30 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 04:02:51 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

static t_room	*build_room(char **params)
{
	t_room	*room;

	if (!(room = ft_memalloc(sizeof(t_room))))
		DEFAULT_ERROR;
	room->name = params[0];
	if (!set_int(params[1], &room->pos_x) || !set_int(params[2], &room->pos_y))
	{
		free(room);
		return (NULL);
	}
	return (room);
}

static t_room	*find_room(t_room **rooms, int size, char *name)
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

t_room			*add_room(t_graph *graph, char **params)
{
	t_room	**tmp;
	t_room	*room;

	if (arr_size(params) != 3
		|| !*params[0]
		|| *params[0] == 'L'
		|| find_room(graph->rooms, graph->num_rooms, params[0])
		|| !(room = build_room(params)))
	{
		free(params);
		return (NULL);
	}
	tmp = graph->rooms;
	if (!(graph->rooms = ft_memalloc(sizeof(t_room) * (graph->num_rooms + 1))))
		DEFAULT_ERROR;
	ft_memcpy(graph->rooms, tmp, sizeof(t_room) * graph->num_rooms);
	room->id = graph->num_rooms;
	graph->rooms[graph->num_rooms++] = room;
	free(tmp);
	free(params);
	return (room);
}

static void		add_link(t_room *dst, t_room *to_add)
{
	t_room	**tmp;

	if (!ft_strcmp(dst->name, to_add->name)
		|| find_room(dst->links, dst->num_links, to_add->name))
		return ;
	tmp = dst->links;
	if (!(dst->links = ft_memalloc(sizeof(t_room) * (dst->num_links + 1))))
		DEFAULT_ERROR;
	ft_memcpy(dst->links, tmp, sizeof(t_room) * dst->num_links);
	dst->links[dst->num_links++] = to_add;
	free(tmp);
}

t_bool			link_rooms(t_graph *graph, char **params)
{
	t_room	*a;
	t_room	*b;

	if (arr_size(params) != 2
		|| !(a = find_room(graph->rooms, graph->num_rooms, params[0]))
		|| !(b = find_room(graph->rooms, graph->num_rooms, params[1])))
	{
		free(params);
		return (FALSE);
	}
	add_link(a, b);
	add_link(b, a);
	free(params);
	return (TRUE);
}
