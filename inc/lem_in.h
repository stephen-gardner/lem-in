/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:25:53 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 03:53:32 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <errno.h>
# include "libft.h"

# include <stdio.h> // REMOVE BEFORE SUBMISSION

# define FATAL_ERROR(msg)	fatal_error(msg)
# define DEFAULT_ERROR		FATAL_ERROR(strerror(errno))

# define TRIM(x)			trim(x, " \t\v\f\r")

typedef struct	s_line
{
	char			*data;
	struct s_line	*next;
}				t_line;

typedef struct	s_room
{
	char			*name;
	int				id;
	int				pos_x;
	int				pos_y;
	int				ants;
	int				priority;
	int				num_links;
	struct s_room	**links;
}				t_room;

typedef struct	s_graph
{
	t_room			**rooms;
	t_room			*start;
	t_room			*end;
	t_line			*lines;
	int				ants;
	int				num_rooms;
}				t_graph;

/*
** load.c
*/

void			load_graph(t_graph *graph);

/*
** main.c
*/

void			fatal_error(char *msg);

/*
** print.c
*/

void			print_loadout(t_graph *graph);

/*
** room.c
*/

t_room			*add_room(t_graph *graph, char **params);
t_bool			link_rooms(t_graph *graph, char **params);

/*
** util.c
*/

int				arr_size(char **arr);
t_bool			set_int(char *s, int *coord);
char			**split(char *raw, char delim);
char			*trim(char *raw, char *delim);
#endif
