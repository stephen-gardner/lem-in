/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:01:30 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/21 17:30:15 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

t_room	*add_room(t_graph *graph, char **params)
{
	t_room	**tmp;
	t_room	*room;

	if (*params[0] == '#'
		|| *param[0] == 'L'
		|| find_room(graph->rooms, graph->num_rooms, params[0])
		|| !(room = build_room(params)))
	{
		free(params);
		return (NULL);
	}
	tmp = graph->rooms;
	if (!(graph->rooms = ft_memalloc(graph->num_rooms + 1)))
		DEFAULT_ERROR;
	ft_memcpy(graph->rooms, tmp, graph->num_rooms);
	graph->rooms[graph->num_rooms++] = room;
	free(tmp);
	free(params);
	return (room);
}

t_bool	link_rooms(t_graph *graph, char **params)
{
	t_room	*a;
	t_room	*b;

	if (!(a = find_room(graph->rooms, graph->num_rooms, params[0]))
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
