/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:07:40 by bpleutin          #+#    #+#             */
/*   Updated: 2023/05/24 12:42:33 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	slot_selection(char c)
{
	if (c == '1')
		return (1);
	else if (c == 'P' && g_direction == 2)
		return (2);
	else if (c == 'P' && g_direction == 3)
		return (3);
	else if (c == 'C')
		return (4);
	else if (c == 'E')
		return (5);
	else if (c == 'Z' && g_zoom == 12)
		return (12);
	else if (c == 'Z' && g_zoom == 13)
		return (13);
	return (0);
}

void	mapfree(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**ft_mapdup(char **map)
{
	int		i;
	char	**res;

	i = 0;
	while (map[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (map[i])
	{
		res[i] = ft_strdup(map[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

t_position	get_position(char tag, char **map)
{
	int			i;
	int			j;
	t_position	res;

	i = 0;
	res.i = 0;
	res.j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == tag)
			{
				res.i = i;
				res.j = j;
			}
			j++;
		}
		i++;
	}
	return (res);
}

void	print_error(char *msg)
{
	ft_printf("%s", msg);
	exit(EXIT_FAILURE);
}
