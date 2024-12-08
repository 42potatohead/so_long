#include "so_long.h"

int display_exit(t_game *game)
{
	if (game->data.coinscltd == game->mapdata.coins)
	{
		mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->exit.xpm_ptr, (game->mapdata.exit_i * 32), (game->mapdata.exit_j * 32));
		return 1;
	}
	return 1;
}

int	key_handlers(int keycode, t_game *game)
{
	if(keycode == XK_Escape)
	{
		ft_close(game, 1, "Game closed successfully");
	}
	ft_movement(keycode, game);
	return (0);
}
void ft_movement(int keycode, t_game *game)
{
	if (keycode == XK_w)
		if (game->mapdata.row[game->render.player_j - 1][game->render.player_i] != WALL)
		{
			game->render.dir = 'w';
			ft_playermove(game, game->render.player_i, game->render.player_j - 1);
		}
	if (keycode == XK_s)
		if (game->mapdata.row[game->render.player_j + 1][game->render.player_i] != WALL)
		{
			game->render.dir = 's';
			ft_playermove(game, game->render.player_i, game->render.player_j + 1);
		}
	if (keycode == XK_a)
		if (game->mapdata.row[game->render.player_j][game->render.player_i - 1] != WALL)
		{
			game->render.dir = 'a';
			ft_playermove(game, game->render.player_i - 1, game->render.player_j);
		}
	if (keycode == XK_d)
		if (game->mapdata.row[game->render.player_j][game->render.player_i + 1] != WALL)
		{
			game->render.dir = 'd';
			ft_playermove(game, game->render.player_i + 1, game->render.player_j);
		}
}

void ft_free_img(t_game *game)
{
	mlx_destroy_image(game->data.mlx_ptr, game->player.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->coins.xpm_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->exit.xpm_ptr);
}

void ft_free_map(t_game *game)
{
	int i = 0;
	while(game->mapdata.row[i] != NULL)
	{
		free(game->mapdata.row[i]);
		i++;
	}
	free(game->mapdata.row);
}

int ft_close(t_game *game, int code, char *msg)
{
	ft_printf("%s", msg);
	ft_free_img(game);
	if (game->mapdata.mapalloc == 1)
		ft_free_map(game);
	mlx_destroy_window(game->data.mlx_ptr, game->data.window);
	mlx_destroy_display(game->data.mlx_ptr);
	free(game->data.mlx_ptr);
	exit(code);
}

void win_game(t_game *game)
{
	// ft_printf("Chicken escaped!! You won the game! \n");
	ft_close(game, 1, "Chicken escaped!! You won the game!");
}
