/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:03:37 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/24 19:34:24 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_valid_ch(t_game *game, char ch)
{
	if (ch != 'C' && ch != '1' && ch != 'P' && ch != 'E'
		&& ch != '0' && ch != '\n')
		game->mapdata.invalid++;
	if (ch == coins)
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
	if (game->mapdata.coins < 1)
		ft_close(game, 1, "Error\nShould be at least one coin");
	if (game->mapdata.invalid != 0)
		ft_close(game, 1, "Error\ninvalid character in map");
}
