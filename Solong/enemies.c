/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:10:39 by bpleutin          #+#    #+#             */
/*   Updated: 2023/05/24 17:11:13 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	g_zoom = 12;

void	lose_game(t_game *game, t_position p)
{
	game->map[p.i][p.j] = '0';
	mlx_string_put(game->mlx, game->win, ft_strlen(game->map[0]) * 32 - 60,
		(tab_len(game->map) * 64) + 20, 111000000, "haha LOSER");
	game->end = 1;
}

t_position	random_mvt(t_game *game, int i, int j)
{
	int			r;
	t_position	tmp;

	srand(time(NULL));
	tmp.i = i;
	tmp.j = j;
	while (tmp.i == i && tmp.j == j)
	{
		r = rand() % 4;
		if (r == 0 && (game->map[i][j - 1] == '0' || game->map[i][j - 1] == 'P'))
		{
			g_zoom = 13;
			tmp.j = j - 1;
		}
		else if (r == 1 && (game->map[i][j + 1] == '0' || game->map[i][j + 1] == 'P'))
		{
			g_zoom = 12;
			tmp.j = j + 1;
		}
		else if (r == 2 && (game->map[i - 1][j] == '0' || game->map[i - 1][j] == 'P'))
			tmp.i = i - 1;
		else if (r == 3 && (game->map[i + 1][j] == '0' || game->map[i + 1][j] == 'P'))
			tmp.i = i + 1;
	}
	return (tmp);
}

void	move_zoom(t_game *game)
{
	int			i;
	int			j;
	t_position	new;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'Z' && (i != new.i || j != new.j))
			{
				new = random_mvt(game, i, j);
				if (game->map[new.i][new.j] == 'P')
					lose_game(game, new);
				game->map[i][j] = '0';
				game->map[new.i][new.j] = 'Z';
				mlx_put_image_to_window(game->mlx, game->win,
					game->img[0][0].ptr, j * 64, i * 64);
				mlx_put_image_to_window(game->mlx, game->win,
					game->img[g_zoom][0].ptr, new.j * 64, new.i * 64);
			}
		}
	}
}
