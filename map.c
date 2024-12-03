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
	if (game->mapdata.row[game->render.player_j][game->render.player_i] == COINS)
	{
		game->mapdata.row[game->render.player_j][game->render.player_i] = WALL;
		game->data.coinscltd++;
		ft_printf("Coins Collected : %d \n", game->data.coinscltd);
	}
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
	int i;

	i = 0;
	char *line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		free(line);
		i++;
	}
	game->mapdata.height = i;
}

void ft_checkmap(t_game *game)
{
	int i;
	int j;
	int k;
	int h;

	j = 0;
	i = 0;
	k = 0;
	h = 0;
	game->mapdata.width = 13;
	while (game->mapdata.row[i])
	{
		if (game->mapdata.row[i + 1] != NULL && (strlen(game->mapdata.row[i]) != strlen(game->mapdata.row[i + 1])))
			exit(-1);
		i++;
		if (game->mapdata.row[0] != NULL && (game->mapdata.row[0][j] != WALL))
			exit(-1);
		j++;
		if (game->mapdata.row[game->mapdata.height] != NULL && (game->mapdata.row[game->mapdata.height][h] != WALL))
			exit(-1);
		h++;
		if (game->mapdata.row[j] != NULL && (game->mapdata.row[k][1] != WALL && game->mapdata.row[k][game->mapdata.width]))
			exit(-1);
		k++;
	}
}

void	ft_map(t_game *game, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	ft_calch(game, fd);
	close(fd);
    game->mapdata.row = malloc(sizeof(char *) * (game->mapdata.height + 1));
	if (!game->mapdata.row)
		return ;
	fd = open(av[1], O_RDONLY);
	if(!ft_readmap(game, fd))
		{ft_printf("Error reading map."); exit(0);}
	ft_checkmap(game);
	ft_rendermap(game);

}
