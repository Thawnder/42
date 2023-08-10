/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:34:39 by bpleutin          #+#    #+#             */
/*   Updated: 2023/05/24 10:54:00 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	g_stop = 0;
int	g_found = 1;
int	g_items = 0;

void	check_path(char **map, int i, int j, int limit)
{
	if (map[i][j] == '1' || map[i][j] == 'X' || g_stop == 1)
		return ;
	if (map[i][j] == 'E' || map[i][j] == 'C')
		g_found++;
	if (g_found == limit)
		g_stop = 1;
	map[i][j] = 'X';
	check_path(map, i + 1, j, limit);
	check_path(map, i - 1, j, limit);
	check_path(map, i, j + 1, limit);
	check_path(map, i, j - 1, limit);
}

int	check_content(char **map)
{
	int			i;
	int			j;
	static int	flag_e = 0;
	static int	flag_p = 0;

	i = 0;
	while (map[++i + 1])
	{
		j = 0;
		while (map[i][++j + 1])
		{
			if (map[i][j] == 'C')
				g_items++;
			if (map[i][j] == 'E')
				flag_e++;
			if (map[i][j] == 'P')
				flag_p++;
		}
	}
	if (g_items < 1 || flag_e != 1 || flag_p != 1)
		print_error("Map content doesn't follow rules\n");
	return (g_items + flag_e + flag_p);
}

void	check_walls(char c1, char c2, int flag)
{
	if (c1 != '1' || c2 != '1')
	{
		if (flag == 1)
			print_error("Map isn't surrounded by walls (Left/Right)\n");
		else
			print_error("Map isn't surrounded by walls (Up/Down)\n");
	}
}

void	check_map(char **map)
{
	int		i;
	int		j;
	int		size;
	char	**tmp;

	size = ft_strlen(map[0]);
	if (size == 0)
		print_error("Map is empty.\n");
	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) != (size_t) size)
			print_error("Map isn't square shaped.\n");
		check_walls(map[i][0], map[i][size - 1], 1);
	}
	j = -1;
	while (++j < size)
		check_walls(map[0][j], map[i - 1][j], 0);
	tmp = ft_mapdup(map);
	i = get_position('P', map).i;
	j = get_position('P', map).j;
	check_path(tmp, i, j, check_content(map));
	mapfree(tmp);
	if (g_stop == 0)
		print_error("Item or exit not attainable.\n");
}

int	check_errors(int args, char *map)
{
	int		fd;
	char	*res;

	if (args != 2)
		print_error("Wrong input. Execution should be: ./so_long [file]\n");
	res = ft_strchr(map, '.');
	if (!res || (res != ft_strrchr(map, '.') && res[0] == '.'
			&& res[1] == 'b' && res[2] == 'e' && res[3] == 'r'))
		print_error("Map format is invalid.\n");
	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error("Map file does not exist\n");
	return (fd);
}
