#include "so_long.h"

//#include "./libft/libft.h"

// # include <mlx.h>

// void ft_map(t_data data, t_mapdata s_mapdata, t_render s_render, int x, int y)
// {
// 	while (mapdata->row[i])
// 	{
// 		if (mapdata->row[i] == '1')
// 			mlx_put_image_to_window(data.init, data.window, render.img, x,y);
// 		x *= 2.5;
// 		i++;
// 	}
// }

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// void	ft_player(t_game *game, int x, int y)
// {
// 	mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
// 					game->render.wall, x, y);
// }
void ft_rendermap(t_game *game)
{
	int i, x, y, j, len;

	x = 0; y = 0; j = 0;
	i = 0;
	len = ft_strlen(game->mapdata.row[0]);
	while(game->mapdata.row[j])
	{
		i = 0;
		x = 0;
		while (i < len)
		{
			if (game->mapdata.row[j][i] == WALL)
				mlx_put_image_to_window(game->data.mlx_ptr, game->data.window,
					game->wall.xpm_ptr, (i * 48.5), (j * 48.5));
			i++;
		}
		j++;
	}
}

int	key_handlers(int keycode, t_game *game)
{
	if(keycode == XK_Escape)
	{
		mlx_destroy_window(game->data.mlx_ptr, game->data.window);
		mlx_destroy_display(game->data.mlx_ptr);
		free(game->data.mlx_ptr);
		exit(0);
	}
	// if (keycode == XK_w)
	// {
	// 	ft_player(game, game->render.x, game->render.y + 50);
	// }
	return (0);
}

int ft_close(t_game *game)
{
    int i;

    i = 0;
    while (i < game->mapdata.height)
    {
        free(game->mapdata.row[i]);
        i++;
    }
    free(game->mapdata.row);
    mlx_destroy_window(game->data.mlx_ptr, game->data.window);
    mlx_destroy_display(game->data.mlx_ptr);
    free(game->data.mlx_ptr);
    exit(0);
    return (0);
}

void read_map(t_game *game)
{
    game->mapdata.height = 3;
    game->mapdata.width = 7;

    game->mapdata.row = malloc(sizeof(char *) * (game->mapdata.height + 1));
    if (!game->mapdata.row)
        return;

    game->mapdata.row[0] = ft_strdup("1111111");
    game->mapdata.row[1] = ft_strdup("1000001");
    game->mapdata.row[2] = ft_strdup("1111111");
    game->mapdata.row[3] = NULL;
}

int	main(void)
{
	t_game game;

	read_map(&game);
	// game.render.wall = "./1.xpm";
	game.data.mlx_ptr = mlx_init();
	if (!game.data.mlx_ptr)
		return (1);
	game.data.window = mlx_new_window(game.data.mlx_ptr, 400, 400, "WOW");
	if(!game.data.window)
		return (free(game.data.mlx_ptr), 1);

	mlx_hook(game.data.window, 17, 0, ft_close, &game);
	mlx_hook(game.data.window, KeyPress, KeyRelease, key_handlers, &game);
	game.wall.xpm_ptr = mlx_xpm_file_to_image(game.data.mlx_ptr, "./imgs/Chicken.xpm",
		&game.render.img_height, &game.render.img_width);
	ft_rendermap(&game);
	mlx_loop(game.data.mlx_ptr);
	return (0);
}
