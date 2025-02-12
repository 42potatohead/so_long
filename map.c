/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:33:31 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/24 19:35:29 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_readmap(t_game *game, int fd)
{
	int	i;

	i = 0;
	game->mapdata.row[i] = get_next_line(fd);
	if (game->mapdata.row[0] == NULL)
		return (0);
	while (game->mapdata.row[i])
	{
		i++;
		game->mapdata.row[i] = get_next_line(fd);
	}
	game->mapdata.row[i] = NULL;
	return (1);
}

void	ft_calch(t_game *game, int fd)
{
	game->mapdata.mapalloc = 0;
	game->mapdata.coins = 0;
	game->mapdata.exits = 0;
	game->mapdata.height = 0;
	parsemap(game, fd);
	if (game->mapdata.exits != 1)
	{
		close(fd);
		ft_close(game, 1, "Error\nWrong number of exits, Must be one");
	}
	if (game->mapdata.players != 1)
	{
		close(fd);
		ft_close(game, 1, "Error\nInvalid Number of Players");
	}
}

void	ft_checkmap(t_game *game)
{
	int	i;

	i = -1;
	while (game->mapdata.row[0][++i + 1] != '\0')
		if (game->mapdata.row[0] != NULL && game->mapdata.row[0][i] != wall)
			ft_close(game, 1, "Error\nInvalid Map");
	i = -1;
	while (game->mapdata.row[game->mapdata.height - 1][++i + 1] != '\0')
		if (game->mapdata.row[game->mapdata.height - 1] != NULL
			&& game->mapdata.row[game->mapdata.height - 1][i] != wall)
			ft_close(game, 1, "Error\nInvalid Map");
	i = 0;
	while (game->mapdata.row[i])
	{
		if (game->mapdata.row[i + 1] != NULL
			&& (ft_strlen(game->mapdata.row[i])
				!= ft_strlen(game->mapdata.row[i + 1])))
			ft_close(game, 1, "Error\nInvalid Map");
		if (game->mapdata.row[i] != NULL && (game->mapdata.row[i][0] != wall
			|| game->mapdata.row[i][game->mapdata.width - 2] != wall))
			ft_close(game, 1, "Error\nInvalid Map");
		i++;
	}
}

void	ft_map(t_game *game, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (!ft_readmap(game, fd))
	{
		close(fd);
		ft_close(game, 0, "Error\nError reading map.");
	}
	close(fd);
	ft_checkmap(game);
	ft_rendermap(game);
	if (game->data.coinscltd == game->mapdata.coins)
		render_object(game, game->exit);
	if (!ft_checkpath(*game, game->render.plyr_j, game->render.plyr_i))
		ft_close(game, 1, "Error\nExit or collectibles are not within reach");
}
