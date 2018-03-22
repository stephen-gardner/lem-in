/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:21:49 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/22 02:39:55 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "lem_in.h"

int			arr_size(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		++size;
	return (size);
}

t_bool		set_int(char *s, int *coord)
{
	long	n;
	int		sign;

	if (!*s)
		return (FALSE);
	if ((sign = (*s == '-') ? -1 : 1) < 0)
		++s;
	n = 0;
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
		{
			arr[i] = raw;
			TRIM(arr[i++]);
		}
		while (*raw && *raw != delim)
			++raw;
	}
	return (arr);
}

char		*trim(char *raw, char *delim)
{
	char	*tmp;
	int		off;
	int		len;

	if (!*raw)
		return (raw);
	off = 0;
	while (raw[off] && ft_strchr(delim, raw[off]))
		++off;
	tmp = raw + off;
	if ((len = ft_strlen(tmp)) > 0)
		--len;
	while (tmp[len] && ft_strchr(delim, tmp[len]))
		--len;
	ft_memmove(raw, tmp, ++len);
	raw[len] = '\0';
	return (raw);
}
