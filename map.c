#include "so_long.h"
// mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
// 					game->render.wall, x, y);

void ft_rendermap(t_game *game)
{
	int i;
	int j;
	int	len;

	j = 0;
	i = 0;
	len = ft_strlen(game->mapdata.row[0]);
	while(game->mapdata.row[j])
	{
		i = 0;
		while (i < len)
		{
			ft_identify_object(game, i, j);
			i++;
		}
		j++;
	}
}

void render_object(t_game *game, t_img img, int i, int j)
{
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, img.xpm_ptr, (i * 32), (j * 32));
}

void	ft_identify_object(t_game *game, int i, int j)
{
	void *spritesheet = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/chicken-32x32.xpm",
        &game->render.img_width, &game->render.img_height);

	if (game->mapdata.row[j][i] == WALL)
		render_object(game, game->wall, i, j);
	if (game->mapdata.row[j][i] == FLOOR || game->mapdata.row[j][i] == PLAYER)
		render_object(game, game->floor, i, j);
	if (game->mapdata.row[j][i] == PLAYER)
	{
		game->player.xpm_ptr = extract_sprite(game->data.mlx_ptr, spritesheet, 0, 0);
		render_object(game, game->player, i, j);
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

void	ft_map(t_game *game, char **av)
{
	int fd;

	//     game->mapdata.height = 4;
    // game->mapdata.width = 8;

	fd = open(av[1], O_RDONLY);
	ft_calch(game, fd);
	close(fd);
    game->mapdata.row = malloc(sizeof(char *) * (game->mapdata.height + 1));
	if (!game->mapdata.row)
		return ;
	fd = open(av[1], O_RDONLY);
	if(!ft_readmap(game, fd))
		{ft_printf("Error reading map."); exit(0);}
	ft_rendermap(game);

}
