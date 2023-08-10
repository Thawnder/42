/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:31:35 by bpleutin          #+#    #+#             */
/*   Updated: 2023/05/24 17:14:56 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	g_direction = 2;

int	shutdown(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 14)
	{
		j = 0;
		while (j < tab_len(g_sprites[i]))
		{
			mlx_destroy_image(game->mlx, game->img[i][j].ptr);
			j++;
		}
		free(game->img[i]);
		i++;
	}
	free(game->img);
	i = -1;
	while (game->map[++i])
		free(game->map[i]);
	free(game->map);
	mlx_loop_end(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	//mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

void	win_game(t_game *game, t_position p)
{
	game->map[p.i][p.j] = '0';
	mlx_put_image_to_window(game->mlx, game->win,
		game->img[0][0].ptr, p.j * 64, p.i * 64);
	mlx_string_put(game->mlx, game->win, ft_strlen(game->map[0]) * 32 - 60,
		(tab_len(game->map) * 64) + 20, 255255255, "Congrats !");
	game->end = 1;
}

void	update_trail(t_game *game, t_position p, int x, int y)
{
	if (game->trail[0].i)
		game->trail[1] = game->trail[0];
	if (game->idx[0])
		game->idx[1] = game->idx[0];
	if (x != 0 && (!game->lm || !is_vertical(game->lm)))
		game->idx[0] = 6;
	else if (y != 0 && (!game->lm || is_vertical(game->lm)))
		game->idx[0] = 7;
	else if ((x == -1 && (game->lm == UP || game->lm == W))
		|| (y == 1 && (game->lm == RIGHT || game->lm == D)))
		game->idx[0] = 8;
	else if ((x == -1 && (game->lm == DOWN || game->lm == S))
		|| (y == -1 && (game->lm == RIGHT || game->lm == D)))
		game->idx[0] = 9;
	else if ((x == 1 && (game->lm == UP || game->lm == W))
		|| (y == 1 && (game->lm == LEFT || game->lm == A)))
		game->idx[0] = 10;
	else if ((x == 1 && (game->lm == DOWN || game->lm == S))
		|| (y == -1 && (game->lm == LEFT || game->lm == A)))
		game->idx[0] = 11;
	mlx_put_image_to_window(game->mlx, game->win,
		game->img[game->idx[0]][0].ptr, p.j * 64, p.i * 64);
	game->trail[0] = p;
}

void	move_player(t_game *game, int x, int y, int keycode)
{
	static int	collected = 0;
	static int	mvt = 0;
	t_position	p;

	p = get_position('P', game->map);
	if (p.i + y >= tab_len(game->map)
		|| p.j + x >= (int) ft_strlen(game->map[0])
		|| game->map[p.i + y][p.j + x] == '1'
		|| (game->map[p.i + y][p.j + x] == 'E' && collected != g_items))
		return ;
	update_count(game, ++mvt);
	game->map[p.i][p.j] = '0';
	update_trail(game, p, x, y);
	if (game->map[p.i + y][p.j + x] == 'E' && collected == g_items)
		win_game(game, p);
	if (game->map[p.i + y][p.j + x] == 'Z')
		lose_game(game, p);
	if (game->end == 1)
		return ;
	if (game->map[p.i + y][p.j + x] == 'C')
		collected++;
	game->map[p.i + y][p.j + x] = 'P';
	mlx_put_image_to_window(game->mlx, game->win,
		game->img[g_direction][0].ptr, (p.j + x) * 64, (p.i + y) * 64);
	game->lm = keycode;
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		shutdown(game);
	if (game->end == 1)
		return (0);
	if (keycode == W || keycode == UP)
		move_player(game, 0, -1, keycode);
	if (keycode == A || keycode == LEFT)
	{
		g_direction = 3;
		move_player(game, -1, 0, keycode);
	}
	if (keycode == S || keycode == DOWN)
		move_player(game, 0, 1, keycode);
	if (keycode == D || keycode == RIGHT)
	{
		g_direction = 2;
		move_player(game, 1, 0, keycode);
	}
	if (game->end == 0)
		move_zoom(game);
	return (0);
}
