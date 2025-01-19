/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:33:31 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/19 12:44:58 by zabu-bak         ###   ########.fr       */
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

void is_valid_ch(t_game *game, char ch)
{

	if (ch != 'C' && ch != '1' && ch != 'P' && ch != 'E' && ch != '0' && ch != '\n')
		game->mapdata.invalid++;
	if (ch == COINS)
		game->mapdata.coins++;
	if (ch == 'E')
		game->mapdata.exits++;
	if (ch == 'P')
		game->mapdata.players++;
}

void	parsemap(t_game *game, int fd)
{
	char	*line;
	int		ch;
	game->mapdata.invalid = 0;
	game->mapdata.players = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (game->mapdata.height == 0)
			game->mapdata.width = ft_strlen(line);
		ch = 0;
		while (line[ch] != '\0')
		{
			is_valid_ch(game, line[ch]);
			ch++;
		}
		free(line);
		game->mapdata.height++;
	}
	if (game->mapdata.invalid != 0)
		ft_close(game, 1, "invalid character in map");

}

void	ft_calch(t_game *game, int fd)
{
	game->mapdata.mapalloc = 0;
	game->mapdata.coins = 0;
	game->mapdata.exits = 0;
	game->mapdata.height = 0;
	parsemap(game, fd);
	if (game->mapdata.exits != 1)
		ft_close(game, 1, "Wrong number of exits, Must be one");
	printf("%d\n", game->mapdata.players);
	if(game->mapdata.players != 0)
		ft_close(game, 1, "Invalid Number of Players");
}

void	ft_checkmap(t_game *game)
{
	int	i;

	i = -1;
	while (game->mapdata.row[0][++i + 1] != '\0')
		if (game->mapdata.row[0] != NULL && game->mapdata.row[0][i] != WALL)
			ft_close(game, 1, "Invalid Map");
	i = -1;
	while (game->mapdata.row[game->mapdata.height - 1][++i + 1] != '\0')
		if (game->mapdata.row[game->mapdata.height - 1] != NULL
			&& game->mapdata.row[game->mapdata.height - 1][i] != WALL)
			ft_close(game, 1, "Invalid Map");
	i = 0;
	while (game->mapdata.row[i])
	{
		if (game->mapdata.row[i + 1] != NULL
			&& (ft_strlen(game->mapdata.row[i])
				!= ft_strlen(game->mapdata.row[i + 1])))
			ft_close(game, 1, "Invalid Map");
		if (game->mapdata.row[i] != NULL && (game->mapdata.row[i][0] != WALL
			|| game->mapdata.row[i][game->mapdata.width - 2] != WALL))
			ft_close(game, 1, "Invalid Map");
		i++;
	}
}

void	ft_map(t_game *game, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (!ft_readmap(game, fd))
	{
		ft_printf("Error reading map.");
		exit(0);
	}
	ft_checkmap(game);
	ft_rendermap(game);
	if (game->data.coinscltd == game->mapdata.coins)
		render_object(game, game->exit);
	if (!ft_checkpath(*game, game->render.plyr_j, game->render.plyr_i))
		ft_close(game, 1, "Exit or collectibles are not within reach");
}
