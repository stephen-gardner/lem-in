/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:23:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 03:48:00 by sgardner         ###   ########.fr       */
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
	return (0);
}
