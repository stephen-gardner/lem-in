/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:23:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 05:03:57 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "lem_in.h"

void		fatal_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

static void	cleanup(t_graph *graph)
{
	void	*next;
	int		i;

	while (graph->lines)
	{
		next = graph->lines->next;
		free(graph->lines->data);
		free(graph->lines);
		graph->lines = next;
	}
	i = 0;
	while (i < graph->num_rooms)
	{
		free(graph->rooms[i]->links);
		free(graph->rooms[i++]);
	}
	free(graph->rooms);
}

int			main(void)
{
	t_graph	graph;

	ft_memset(&graph, 0, sizeof(t_graph));
	load_graph(&graph);
	if (graph.ants < 1 || graph.num_rooms < 1 || !graph.start || !graph.end)
		FATAL_ERROR("ERROR");
	print_loadout(&graph);
	if (graph.start == graph.end)
		return (0);
	cleanup(&graph);
	return (0);
}
