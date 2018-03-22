/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:23:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 00:21:38 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_layout(t_graph *graph)
{
	printf("start: %s\n", graph->start->name);
	printf("end: %s\n", graph->end->name);
	int i = 0;
	while (i < graph->num_rooms)
	{
		t_room *room = graph->rooms[i++];
		printf("Name: %s X: %d Y: %d\n", room->name, room->pos_x, room->pos_y);
		int j = 0;
		while (j < room->num_links)
		{
			t_room *link = room->links[j++];
			printf(" - %s\n", link->name);
		}
	}
}

int main(void)
{
	t_graph	graph;

	ft_memset(&graph, 0, sizeof(t_graph));
	load_graph(&graph);
	print_layout(&graph); // DEBUG
	return (0);
}
