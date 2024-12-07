#include "so_long.h"

void ft_rendermap(t_game *game)
{
	int	len;

	game->render.j = 0;
	game->render.i = 0;
	len = ft_strlen(game->mapdata.row[0]);
	while(game->mapdata.row[game->render.j])
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

void render_object(t_game *game, t_img img)
{
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, img.xpm_ptr, (game->render.i * 32), (game->render.j * 32));
}

void ft_playermove(t_game *game, int i, int j)
{
	game->render.player_i = i;
	game->render.player_j = j;
	printf("%d %d \n", game->render.player_j, game->render.player_i);
	if (game->mapdata.row[game->render.player_j][game->render.player_i] == COINS)
	{
		game->mapdata.row[game->render.player_j][game->render.player_i] = FLOOR;
		game->data.coinscltd++;
		ft_printf("Coins Collected : %d \n", game->data.coinscltd);
	}
	if (game->mapdata.row[game->render.player_j][game->render.player_i] == 'E' && game->data.coinscltd == game->mapdata.coins)
		win_game(game);
	ft_printf("# of Moves : %d\n", game->data.mvcount++);
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->player.xpm_ptr, (i *32), (j * 32));
	if(game->render.dir == 'w')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->floor.xpm_ptr, (i *32), ((j + 1) * 32));
	if(game->render.dir == 's')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->floor.xpm_ptr, (i *32), ((j - 1) * 32));
	if(game->render.dir == 'a')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->floor.xpm_ptr, ((i + 1) * 32), (j * 32));
	if(game->render.dir == 'd')
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->floor.xpm_ptr, ((i - 1) * 32), (j * 32));

}

void	ft_identify_object(t_game *game)
{
	if (game->mapdata.row[game->render.j][game->render.i] == WALL)
		render_object(game, game->wall);
	if (game->mapdata.row[game->render.j][game->render.i] == FLOOR)
		render_object(game, game->floor);
	if (game->mapdata.row[game->render.j][game->render.i] == COINS)
		render_object(game, game->coins);
	if (game->mapdata.row[game->render.j][game->render.i] == PLAYER)
	{
		game->render.player_i = game->render.i;
		game->render.player_j = game->render.j;
		render_object(game, game->player);
	}
}

int	ft_readmap(t_game *game, int fd)
{
	int i = 0;

	game->mapdata.row[i] = get_next_line(fd);
	if(game->mapdata.row[0] == NULL)
		return 0;
	while(game->mapdata.row[i])
		{i++; game->mapdata.row[i] = get_next_line(fd);}
	game->mapdata.row[i] = NULL;
	return 1;
}
void ft_calch(t_game *game, int fd)
{
	char *line;
	int i;
	int ch;

	game->mapdata.mapalloc = 0;
	game->mapdata.coins = 0;
	game->mapdata.exits = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		ch = 0;
		while (line[ch] != '\0')
		{
			if (line[ch] == COINS)
				game->mapdata.coins++;
			if (line[ch] == 'E')
				game->mapdata.exits++;
			ch++;
		}
		free(line);
		i++;
	}
	if (game->mapdata.exits != 1)
		ft_close(game);
	game->mapdata.height = i;
}

void ft_checkmap(t_game *game)
{
	int i;

	i = -1;
	while(game->mapdata.row[0][++i + 1] != '\0')
		if (game->mapdata.row[0] != NULL && game->mapdata.row[0][i] != WALL)
			ft_close(game);
	i = -1;
	while(game->mapdata.row[game->mapdata.height - 1][++i + 1] != '\0')
		if (game->mapdata.row[game->mapdata.height - 1] != NULL && game->mapdata.row[game->mapdata.height - 1][i] != WALL)
			ft_close(game);
	i = 0;
	game->mapdata.width = 13;
	while (game->mapdata.row[i])
	{
		if (game->mapdata.row[i + 1] != NULL && (ft_strlen(game->mapdata.row[i]) != ft_strlen(game->mapdata.row[i + 1])))
			ft_close(game);
		if (game->mapdata.row[i] != NULL && (game->mapdata.row[i][0] != WALL || game->mapdata.row[i][game->mapdata.width - 2] != WALL))
			ft_close(game);
		i++;
	}
}

void fill(t_game game, int j, int i, int *coll)
{
	printf("%d %d %d \n",i , j ,game.mapdata.height - 1);
	if (j < 0 || i < 0 || j == game.mapdata.height - 1 || i == 12 || game.mapdata.row[j][i] == '1')
		return ;
	// if (game.mapdata.row[j][i] == WALL)
	// 	return ;
	if (game.mapdata.row[j][i] == COINS)
		*(coll) += 1;

	game.mapdata.row[j][i] = '1';

	fill(game, j + 1 , i, coll);
	fill(game, j - 1 , i, coll);
	fill(game, j , i + 1, coll);
	fill(game, j , i - 1, coll);
}

int	ft_checkpath(t_game game, int j, int i)
{
	int coll = 0;
	printf("%d %d \n", j , i);
	fill(game, j, i, &coll);
	if(coll == game.mapdata.coins)
		return (1);
	printf("%d", coll);
	return 0;
}

void	ft_map(t_game *game, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	ft_calch(game, fd);
	close(fd);
	game->mapdata.mapalloc = 1;
    game->mapdata.row = malloc(sizeof(char *) * (game->mapdata.height + 1));
	if (!game->mapdata.row)
		return ;
	fd = open(av[1], O_RDONLY);
	if(!ft_readmap(game, fd))
		{ft_printf("Error reading map."); exit(0);}
	printf("%d %d \n", game->render.player_j, game->render.player_i);
	ft_checkmap(game);
	if(!ft_checkpath(*game, game->render.player_j, game->render.player_i))
		ft_printf("Exit or collectibles are not within reach");
	ft_rendermap(game);

}
