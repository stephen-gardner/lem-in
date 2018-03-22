/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:25:53 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 22:15:00 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <errno.h>
# include "libft.h"

# define FATAL_ERROR(msg)	fatal_error(msg)
# define DEFAULT_ERROR		FATAL_ERROR(strerror(errno))

typedef struct	s_room
{
	char			*name;
	int				pos_x;
	int				pos_y;
	int				ants;
	int				num_links;
	struct s_room	**links;
}				t_room;

typedef struct	s_graph
{
	int				num_rooms;
	t_room			**rooms;
	t_room			*start;
	t_room			*end;
}				t_graph;

/*
** room.c
*/

t_room			*add_room(t_graph *graph, char **params);
t_bool			link_rooms(t_graph *graph, char **params);

/*
** room_helper.c
*/

t_room			*build_room(char **params);
t_room			*find_room(t_room **rooms, int size, char *name);
void			add_link(t_room *dst, t_room *to_add);

/*
** util.c
*/

void			fatal_error(char *msg);
t_bool			set_pos(char *s, int *coord);
char			**split(char *raw, char delim);
#endif
