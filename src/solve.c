/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 06:30:28 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 07:57:19 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "lem_in.h"

static t_bool	find_shortest(t_queue *queue, t_room *end)
{
	t_room	*room;
	t_room	*link;
	int		i;

	while (!queue_isempty(queue))
	{
		if ((room = dequeue(queue)) == end)
			break ;
		i = 0;
		while (i < room->num_links)
		{
			link = room->links[i++];
			if (!link->parent)
			{
				link->parent = room;
				enqueue(queue, link);
			}
		}
	}
	while (!queue_isempty(queue))
		dequeue(queue);
	free(queue);
	return (room == end);
}

static void		fix_path(t_room *start, t_room *end)
{
	end->links[0] = NULL;
	while (end)
	{
		end->parent->links[0] = end;
		end = (end->parent != start) ? end->parent : NULL;
	}
}

static void		move_ants(t_queue *queue)
{
	t_ant	*ant;
	t_node	*node;
	t_node	*next;

	node = queue->start;
	while (node)
	{
		ant = node->content;
		ant->room = ant->room->links[0];
		write(1, "L", 1);
		ft_putnbr(ant->id);
		write(1, "-", 1);
		write(1, ant->room->name, ft_strlen(ant->room->name));
		next = node->next;
		if (!ant->room->links[0])
			free(dequeue(queue));
		if ((node = next))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

static void		navigate(t_graph *graph)
{
	t_ant	*ant;
	t_queue	*queue;
	int		i;

	i = 1;
	queue = queue_init();
	while (i <= graph->ants || !queue_isempty(queue))
	{
		if (i <= graph->ants)
		{
			ant = ft_memalloc(sizeof(t_ant));
			ant->id = i++;
			ant->room = graph->start;
			enqueue(queue, ant);
		}
		if (!queue_isempty(queue))
			move_ants(queue);
	}
	free(queue);
}

void			solve(t_graph *graph)
{
	t_queue	*queue;

	queue = queue_init();
	graph->start->parent = graph->start;
	enqueue(queue, graph->start);
	if (!find_shortest(queue, graph->end))
		FATAL_ERROR("ERROR");
	print_loadout(graph);
	write(1, "\n", 1);
	fix_path(graph->start, graph->end);
	navigate(graph);
}
