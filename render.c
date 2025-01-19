/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:50:27 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/19 13:02:49 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_rendermap(t_game *game)
{
	int	len;

	game->render.j = 0;
	game->render.i = 0;
	game->mapdata.exit_j = 0;
	game->mapdata.exit_i = 0;
	len = ft_strlen(game->mapdata.row[0]);
	while (game->mapdata.row[game->render.j])
	{
		game->render.i = 0;
		while (game->render.i < len)
		{
			ft_identify_object(game);
			game->render.i++;
		}
		game->render.j++;
	}
}

void	render_object(t_game *game, t_img img)
{
	mlx_put_image_to_window(game->data.mlx_ptr,
		game->data.window,
		img.xpm_ptr,
		(game->render.i * TILE_SIZE),
		(game->render.j * TILE_SIZE)
		);
}

void	ft_trailing(t_game *game, int i, int j)
{
	if (game->render.dir == 'w')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
			game->floor.xpm_ptr, (i * TILE_SIZE), ((j + 1) * TILE_SIZE));
	if (game->render.dir == 's')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
			game->floor.xpm_ptr, (i * TILE_SIZE), ((j - 1) * TILE_SIZE));
	if (game->render.dir == 'a')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
			game->floor.xpm_ptr, ((i + 1) * TILE_SIZE), (j * TILE_SIZE));
	if (game->render.dir == 'd')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
			game->floor.xpm_ptr, ((i - 1) * TILE_SIZE), (j * TILE_SIZE));
}

void	ft_playermove(t_game *game, int i, int j, int keycode)
{
	game->render.plyr_i = i;
	game->render.plyr_j = j;
	if (game->mapdata.row[game->render.plyr_j][game->render.plyr_i] == COINS)
	{
		game->mapdata.row[game->render.plyr_j][game->render.plyr_i] = FLOOR;
		game->data.coinscltd++;
		ft_printf("Coins Collected : %d / %d \n",
			game->data.coinscltd, game->mapdata.coins);
	}
	if (game->mapdata.row[game->render.plyr_j][game->render.plyr_i] == 'E'
		&& game->data.coinscltd == game->mapdata.coins)
		win_game(game);
	ft_printf("# of Moves : %d\n", game->data.mvcount++);
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
		game->player.xpm_ptr, (i * TILE_SIZE), (j * TILE_SIZE));
	ft_trailing(game, i, j);
}

void	ft_identify_object(t_game *game)
{
	if (game->mapdata.row[game->render.j][game->render.i] == 'E')
	{
		game->mapdata.exit_j = game->render.j;
		game->mapdata.exit_i = game->render.i;
		render_object(game, game->floor);
	}
	if (game->mapdata.row[game->render.j][game->render.i] == WALL)
		render_object(game, game->wall);
	if (game->mapdata.row[game->render.j][game->render.i] == FLOOR)
		render_object(game, game->floor);
	if (game->mapdata.row[game->render.j][game->render.i] == COINS)
		render_object(game, game->coins);
	if (game->mapdata.row[game->render.j][game->render.i] == PLAYER)
	{
		game->render.plyr_i = game->render.i;
		game->render.plyr_j = game->render.j;
		render_object(game, game->player);
	}
}
