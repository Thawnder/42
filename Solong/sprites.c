/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:08 by bpleutin          #+#    #+#             */
/*   Updated: 2023/05/24 17:23:47 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
char	*g_sprites[5][6] = {{"./Sprites/cloud_small.xpm"},
				{"./Sprites/building1.xpm",
				"./Sprites/building2.xpm", 
				"./Sprites/building3.xpm",
				"./Sprites/building4.xpm",
				"./Sprites/building5.xpm", NULL},
				{"./Sprites/raikoutest.xpm"},
				{"./Sprites/energy.xpm"},
				{"./Sprites/energy.xpm"}};
Format de sprites pour la generation random
*/

char	*g_sprites[14][9] = {
{"./Sprites/floor.xpm"},
{"./Sprites/test1.xpm",
	"./Sprites/test2.xpm",
	"./Sprites/test3.xpm",
	"./Sprites/test4.xpm",
	"./Sprites/test5.xpm",
	"./Sprites/test6.xpm",
	NULL},
{"./Sprites/dinoright1.xpm",
	"./Sprites/dinoright2.xpm",
	"./Sprites/dinoright3.xpm",
	"./Sprites/dinoright4.xpm",
	"./Sprites/dinoright5.xpm",
	"./Sprites/dinoright6.xpm",
	NULL},
{"./Sprites/dinoleft1.xpm",
	"./Sprites/dinoleft2.xpm",
	"./Sprites/dinoleft3.xpm",
	"./Sprites/dinoleft4.xpm",
	"./Sprites/dinoleft5.xpm",
	"./Sprites/dinoleft6.xpm",
	NULL},
{"./Sprites/energy.xpm"},
{"./Sprites/idleportal1.xpm",
	"./Sprites/idleportal2.xpm",
	"./Sprites/idleportal3.xpm",
	"./Sprites/idleportal4.xpm",
	"./Sprites/idleportal5.xpm",
	"./Sprites/idleportal6.xpm",
	"./Sprites/idleportal7.xpm",
	"./Sprites/idleportal8.xpm",
	NULL},
{"./Sprites/trail1.xpm",
	"./Sprites/trail2.xpm",
	"./Sprites/trail3.xpm",
	"./Sprites/trail4.xpm",
	NULL},
{"./Sprites/trailup1.xpm",
	"./Sprites/trailup2.xpm",
	"./Sprites/trailup3.xpm",
	"./Sprites/trailup4.xpm",
	NULL},
{"./Sprites/trailLD1.xpm",
	"./Sprites/trailLD2.xpm",
	"./Sprites/trailLD3.xpm",
	"./Sprites/trailLD4.xpm",
	NULL},
{"./Sprites/trailLU1.xpm",
	"./Sprites/trailLU2.xpm",
	"./Sprites/trailLU3.xpm",
	"./Sprites/trailLU4.xpm",
	NULL},
{"./Sprites/trailRD1.xpm",
	"./Sprites/trailRD2.xpm",
	"./Sprites/trailRD3.xpm",
	"./Sprites/trailRD4.xpm",
	NULL},
{"./Sprites/trailRU1.xpm",
	"./Sprites/trailRU2.xpm",
	"./Sprites/trailRU3.xpm",
	"./Sprites/trailRU4.xpm",
	NULL},
{"./Sprites/zoomright1.xpm",
	"./Sprites/zoomright2.xpm",
	"./Sprites/zoomright3.xpm",
	"./Sprites/zoomright4.xpm",
	"./Sprites/zoomright5.xpm",
	"./Sprites/zoomright6.xpm",
	NULL},
{"./Sprites/zoomleft1.xpm",
	"./Sprites/zoomleft2.xpm",
	"./Sprites/zoomleft3.xpm",
	"./Sprites/zoomleft4.xpm",
	"./Sprites/zoomleft5.xpm",
	"./Sprites/zoomleft6.xpm",
	NULL},
};

void	init_sprites(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->img = malloc(sizeof(t_data *) * 14);
	while (i < 14)
	{
		j = 0;
		game->img[i] = malloc(sizeof(t_data) * (tab_len(g_sprites[i]) + 1));
		while (j < tab_len(g_sprites[i]))
		{
			game->img[i][j].ptr = mlx_xpm_file_to_image(game->mlx,
					g_sprites[i][j],
					&game->img[i][j].x, &game->img[i][j].y);
			game->img[i][j].addr = mlx_get_data_addr(game->img[i][j].ptr,
					&game->img[i][j].bpp, &game->img[i][j].length,
					&game->img[i][j].endian);
			j++;
		}
		game->img[i][j].ptr = NULL;
		i++;
	}
}

void	fast_anim(t_game *game, int **it)
{
	int			i;
	int			j;
	int			f;
	int			t;
	t_position	p;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			f = slot_selection(game->map[i][j]);
			p.i = i;
			p.j = j;
			if (f == 2 || f == 3 || f == 5 || f == 12 || f == 13)
				update_anim(game, f, it, p);
			t = is_trail(game, i, j);
			if (f == 0 && t != -1)
				update_anim(game, game->idx[t], it, p);
		}
	}
}

void	wall_anim(t_game *game, int **it)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			f = slot_selection(game->map[i][j]);
			if (f != 2 && f != 3 && f != 5 && f != 12 && f != 13)
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->img[f][(*it)[f]].ptr, j * 64, i * 64);
				incr(&(*it)[f], tab_len(g_sprites[f]) - 1);
			}
			j++;
		}
		i++;
	}
}

int	update_sprites(t_game *game)
{
	static t_frames		frames = {0, 0};
	static int			*it;

	if (game->end == 1)
		return (0);
	if (!it)
		it = (int *)ft_calloc(14, sizeof(int));
	if (frames.f++ > 5000)
	{
		fast_anim(game, &it);
		frames.f = 0;
	}
	if (frames.w++ > 10000)
	{
		wall_anim(game, &it);
		frames.w = 0;
	}
	return (0);
}

void	update_count(t_game *game, int mvt)
{
	mlx_string_put(game->mlx, game->win, ft_strlen(game->map[0]) * 10,
		(tab_len(game->map) * 64) + 20, 000000000, ft_itoa(mvt - 1));
	mlx_string_put(game->mlx, game->win, ft_strlen(game->map[0]) * 10,
		(tab_len(game->map) * 64) + 20, 111000000, ft_itoa(mvt));
}
