/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:26:03 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 00:16:21 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "lem_in.h"

static char		*add_line(t_graph *graph, char *data)
{
	t_line	*line;

	if (!(line = ft_memalloc(sizeof(t_line))))
		DEFAULT_ERROR;
	line->data = data;
	line->next = graph->lines;
	graph->lines = line;
	return (data);
}

static t_bool	load_link(t_graph *graph, char *line)
{
	t_bool	res;

	res = FALSE;
	if (ft_strchr(line, '-'))
		res = link_rooms(graph, split(line, '-'));
	free(line);
	return (res);
}

static t_room	*load_room(t_graph *graph, char *line)
{
	t_room	*res;

	if ((res = add_room(graph, split(line, ' '))))
		add_line(graph, line);
	else
		free(line);
	return (res);
}

static t_bool	parse_cmd(t_graph *graph, char *cmd)
{
	t_room	**target;
	t_room	*room;
	char	*line;

	target = NULL;
	if (!ft_strcmp(cmd, "##start"))
		target = &graph->start;
	else if (!ft_strcmp(cmd, "##end"))
		target = &graph->end;
	else
	{
		free(cmd);
		return (TRUE);
	}
	if (get_next_line(0, &line) < 1)
	{
		free(cmd);
		return (FALSE);
	}
	if ((room = load_room(graph, line)))
		*target = room;
	free(cmd);
	return (room != NULL);
}

void			load_graph(t_graph *graph)
{
	char	*line;
	t_bool	res;

	res = TRUE;
	while (get_next_line(0, &line) > 0)
	{
		trim(line, " \t\v\f\r");
		if (*line == '#')
			res = parse_cmd(graph, line);
		else
		{
			if (ft_strchr(line, ' '))
				res = load_room(graph, line) != NULL;
			else
				res = load_link(graph, line);
		}
		if (!res)
			break ;
	}
}
