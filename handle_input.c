#include "so_long.h"

int	key_handlers(int keycode, t_game *game)
{
	if(keycode == XK_Escape)
	{
		mlx_destroy_window(game->data.mlx_ptr, game->data.window);
		mlx_destroy_display(game->data.mlx_ptr);

		free(game->data.mlx_ptr);
		exit(0);
	}
	return (0);
}

int ft_close(t_game *game)
{
	mlx_destroy_window(game->data.mlx_ptr, game->data.window);
	mlx_destroy_display(game->data.mlx_ptr);
	free(game->data.mlx_ptr);
	exit(0);
}
