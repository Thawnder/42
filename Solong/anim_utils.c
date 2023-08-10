/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:27:33 by bpleutin          #+#    #+#             */
/*   Updated: 2023/05/23 12:38:24 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_anim(t_game *game, int idx, int **it, t_position p)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->img[idx][(*it)[idx]].ptr, p.j * 64, p.i * 64);
	incr(&(*it)[idx], tab_len(g_sprites[idx]) - 1);
}

int	is_trail(t_game *game, int i, int j)
{
	if (i == game->trail[0].i && j == game->trail[0].j)
		return (0);
	else if (i == game->trail[1].i && j == game->trail[1].j)
		return (1);
	return (-1);
}

int	is_vertical(int lm)
{
	if (lm == W || lm == UP || lm == S || lm == DOWN)
		return (1);
	return (0);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	incr(int *it, int limit)
{
	if (*it < limit)
		*it += 1;
	else
		*it = 0;
}
