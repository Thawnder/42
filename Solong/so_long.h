/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:58:09 by bpleutin          #+#    #+#             */
/*   Updated: 2023/05/24 17:16:16 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "Minilibx/mlx.h"
# include "Minilibx/mlx_int.h"
# include "Libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <time.h>

# define ESC 65307
# define W 11
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363

typedef struct s_data
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		length;
	int		x;
	int		y;
	int		endian;
}				t_data;

typedef struct s_position
{
	int	i;
	int	j;
}				t_position;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_data		**img;
	int			lm;
	t_position	trail[2];
	int			idx[2];
	int			end;
}				t_game;

typedef struct s_frames
{
	int	f;
	int	w;
}				t_frames;

/* typedef union u_anim
{
	struct s_entities
	{
		int	floor;
		int	wall;
		int	player;
		int	item;
		int	exit;
	};
	int	entities[5];
}				t_anim; */

extern char	*g_sprites[14][9];
extern int	g_items;
extern int	g_direction;
extern int	g_zoom;

t_position	get_position(char tag, char **map);
char		**ft_mapdup(char **map);
void		mapfree(char **map);
void		print_error(char *msg);
int			shutdown(t_game *game);
int			slot_selection(char c);
void		init_sprites(t_game *game);
int			update_sprites(t_game *game);
void		incr(int *it, int limit);
int			tab_len(char **tab);
void		update_anim(t_game *game, int idx, int **it, t_position p);
void		update_count(t_game *game, int mvt);
int			is_trail(t_game *game, int i, int j);
int			is_vertical(int lm);
int			key_hook(int keycode, t_game *game);
int			check_errors(int args, char *map);
void		move_zoom(t_game *game);
void		lose_game(t_game *game, t_position p);
void		check_map(char **map);

#endif
