/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 02:34:44 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 03:58:26 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lem_in.h"

static void	print_comments(t_line *lines)
{
	while (lines)
	{
		if (*lines->data == '#')
		{
			write(1, lines->data, ft_strlen(lines->data));
			write(1, "\n", 1);
		}
		lines = lines->next;
	}
}

static void	print_links(t_graph *graph)
{
	t_room	*room;
	t_room	*link;
	int		i;
	int		j;

	i = 0;
	while (i < graph->num_rooms)
	{
		room = graph->rooms[i++];
		j = 0;
		while (j < room->num_links)
		{
			link = room->links[j++];
			if (link->id > room->id)
			{
				write(1, room->name, ft_strlen(room->name));
				write(1, "-", 1);
				write(1, link->name, ft_strlen(link->name));
				write(1, "\n", 1);
			}
		}
	}
}

static void	print_rooms(t_graph *graph)
{
	t_room	*room;
	int		i;

	i = 0;
	while (i < graph->num_rooms)
	{
		room = graph->rooms[i++];
		if (room == graph->start)
		{
			write(1, "##start", 7);
			write(1, "\n", 1);
		}
		if (room == graph->end)
		{
			write(1, "##end", 5);
			write(1, "\n", 1);
		}
		write(1, room->name, ft_strlen(room->name));
		write(1, " ", 1);
		ft_putnbr(room->pos_x);
		write(1, " ", 1);
		ft_putnbr(room->pos_y);
		write(1, "\n", 1);
	}
}

void		print_loadout(t_graph *graph)
{
	print_comments(graph->lines);
	ft_putnbr(graph->ants);
	write(1, "\n", 1);
	print_rooms(graph);
	print_links(graph);
}
