/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:50:14 by bpleutin          #+#    #+#             */
/*   Updated: 2023/06/14 15:23:26 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**convert_map(int fd)
{
	char	**res;
	char	*line;
	char	*buffer;
	int		r;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	buffer = malloc(1001);
	r = 1;
	while (r != 0)
	{
		r = read(fd, buffer, 1000);
		buffer[r] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	res = ft_split(line, '\n');
	close(fd);
	free(line);
	check_map(res);
	return (res);
}

void	fill_window(t_game *game)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			tmp = slot_selection(game->map[i][j]);
			mlx_put_image_to_window(game->mlx, game->win,
				game->img[tmp][0].ptr, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	game->map = convert_map(check_errors(argc, argv[1]));
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		print_error("Mlx is null.\n");
	game->win = mlx_new_window(game->mlx,
			ft_strlen(game->map[0]) * 64,
			(tab_len(game->map) * 64) + 25, "VIRUS.EXE");
	mlx_set_font(game->mlx, game->win,
		"-misc-fixed-bold-r-normal--20-0-100-100-c-0-iso10646-1");
	if (game->win == NULL)
		print_error("Window is null.\n");
	mlx_key_hook(game->win, &key_hook, game);
	init_sprites(game);
	fill_window(game);
	mlx_loop_hook(game->mlx, &update_sprites, game);
	mlx_hook(game->win, 17, 0L, shutdown, game);
	mlx_loop(game->mlx);
	return (0);
}
