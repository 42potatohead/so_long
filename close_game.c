/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:00:49 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/10 20:00:58 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_img(t_game *game)
{
	mlx_destroy_image(game->data.mlx_ptr, game->player.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->coins.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->exit.xpm_ptr);
}

void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->mapdata.row[i] != NULL)
	{
		free(game->mapdata.row[i]);
		i++;
	}
	free(game->mapdata.row);
}

int	ft_close(t_game *game, int code, char *msg)
{
	ft_printf("%s", msg);
	if (game->img.initimg == 1)
		ft_free_img(game);
	if (game->mapdata.mapalloc == 1)
		ft_free_map(game);
	if (game->mapdata.initgame == 1)
	{
		mlx_destroy_window(game->data.mlx_ptr, game->data.window);
		mlx_destroy_display(game->data.mlx_ptr);
		free(game->data.mlx_ptr);
	}
	exit(code);
}

void	win_game(t_game *game)
{
	ft_close(game, 1, "Chicken escaped!! You won the game!");
}
