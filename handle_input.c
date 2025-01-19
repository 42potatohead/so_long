/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:59:22 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/10 21:03:14 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	display_exit(t_game *game)
{
	if (game->data.coinscltd == game->mapdata.coins)
	{
		mlx_put_image_to_window(game->data.mlx_ptr,
			game->data.window,
			game->exit.xpm_ptr,
			game->mapdata.exit_i * TILE_SIZE,
			game->mapdata.exit_j * TILE_SIZE);
		return (1);
	}
	return (0);
}

int	key_handlers(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		ft_close(game, 1, "Game closed successfully");
	}
	ft_movement(keycode, game);
	return (0);
}

void	ft_movement(int keycode, t_game *game)
{
	int	i;
	int	j;

	i = game->render.plyr_i;
	j = game->render.plyr_j;
	if (keycode == XK_w && game->mapdata.row[j - 1][i] != WALL)
	{
		game->render.dir = 'w';
		ft_playermove(game, game->render.plyr_i, game->render.plyr_j - 1);
	}
	if (keycode == XK_s && game->mapdata.row[j + 1][i] != WALL)
	{
		game->render.dir = 's';
		ft_playermove(game, game->render.plyr_i, game->render.plyr_j + 1);
	}
	if (keycode == XK_a && game->mapdata.row[j][i - 1] != WALL)
	{
		game->render.dir = 'a';
		ft_playermove(game, game->render.plyr_i - 1, game->render.plyr_j);
	}
	if (keycode == XK_d && game->mapdata.row[j][i + 1] != WALL)
	{
		game->render.dir = 'd';
		ft_playermove(game, game->render.plyr_i + 1, game->render.plyr_j);
	}
}
