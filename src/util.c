/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:21:49 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 18:25:50 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "lem_in.h"

void		fatal_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

t_bool		set_pos(char *s, int *coord)
{
	long	n;
	int		sign;

	if (!*s)
		return (FALSE);
	if ((sign = (*s == '-') ? -1 : 1) < 0)
		++s;
	while (*s)
	{
		if ((unsigned int)(*s - '0') > 9)
			return (FALSE);
		n = (n * 10) + ((*s++ - '0') * sign);
		if (n > INT_MAX || n < INT_MIN)
			return (FALSE);
	}
	*coord = (int)n;
	return (TRUE);
}

static int	count_args(char *raw, char delim)
{
	int	count;

	count = 0;
	while (*raw)
	{
		if (*raw != delim && (*(raw + 1) == delim || !*(raw + 1)))
			++count;
		++raw;
	}
	return (count);
}

char		**split(char *raw, char delim)
{
	char	**arr;
	int		size;
	int		i;

	size = count_args(raw, delim);
	if (!(arr = ft_memalloc(sizeof(char *) * (size + 1))))
		DEFAULT_ERROR;
	i = 0;
	while (*raw)
	{
		while (*raw && *raw == delim)
			*raw++ = '\0';
		if (*raw)
			arr[i++] = raw;
		while (*raw && *raw != delim)
			++raw;
	}
	return (arr);
}
