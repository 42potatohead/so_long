/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:48:39 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/10 19:49:26 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill(t_game game, int j, int i, int *coll)
{
	if (j == 0 || i == 0 || j == game.mapdata.height || i == 33
		|| game.mapdata.tmp_map[j][i] == '1'
		|| game.mapdata.tmp_map[j][i] == 'F')
		return ;
	if (game.mapdata.tmp_map[j][i] == COINS)
		*(coll) += 1;
	if (game.mapdata.tmp_map[j][i] == 'E')
		*(coll) += 1;
	game.mapdata.tmp_map[j][i] = 'F';
	fill(game, j + 1, i, coll);
	fill(game, j - 1, i, coll);
	fill(game, j, i + 1, coll);
	fill(game, j, i - 1, coll);
}

int	ft_checkpath(t_game game, int j, int i)
{
	int	coll;
	int	k;

	coll = 0;
	game.mapdata.tmp_map = malloc(sizeof(char *) * (game.mapdata.height + 1));
	k = 0;
	while (k < game.mapdata.height)
	{
		game.mapdata.tmp_map[k] = ft_strdup(game.mapdata.row[k]);
		k++;
	}
	fill(game, j, i, &coll);
	k = 0;
	while (k < game.mapdata.height)
	{
		free(game.mapdata.tmp_map[k]);
		k++;
	}
	free(game.mapdata.tmp_map);
	if (coll == game.mapdata.coins + 1)
		return (1);
	return (0);
}
