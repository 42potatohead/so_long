/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:12:49 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/10 19:31:10 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_av(int ac, char **av)
{
	char	*last_char;

	if (ac == 2)
	{
		last_char = ft_substr(av[1], (ft_strlen(av[1]) - 4), 4);
		if (ft_strncmp(".ber", last_char, 4))
		{
			ft_printf("Invalid file type, Please try again later. \n");
			free(last_char);
			exit(EXIT_FAILURE);
		}
		if (open(av[1], O_RDONLY) == -1)
		{
			ft_printf("File does not exist \n");
			free(last_char);
			exit(EXIT_FAILURE);
		}
		free(last_char);
	}
	else
	{
		ft_printf("wrong number arguments, Please try again later. \n");
		exit(EXIT_FAILURE);
	}
}

void	ft_initimg(t_game *game)
{
	game->img.initimg = 1;
	game->wall.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr,
			"./imgs/border64.xpm", &game->render.img_height,
			&game->render.img_width);
	game->floor.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr,
			"./imgs/Grass2.xpm", &game->render.img_height,
			&game->render.img_width);
	game->player.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr,
			"./imgs/chicken-single-64wgrass.xpm", &game->render.img_height,
			&game->render.img_width);
	game->coins.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr,
			"./imgs/Soju-w-grass.xpm", &game->render.img_height,
			&game->render.img_width);
	game->exit.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr,
			"./imgs/exit.xpm", &game->render.img_height,
			&game->render.img_width);
}

int	ft_initgame(t_game *game, char **av)
{
	game->mapdata.initgame = 1;
	game->data.mlx_ptr = mlx_init();
	if (!game->data.mlx_ptr)
		return (1);
	game->data.window = mlx_new_window(game->data.mlx_ptr, (game->mapdata.width
				- 1) * TILE_SIZE, game->mapdata.height * TILE_SIZE, "WOW");
	if (!game->data.window)
		return (free(game->data.mlx_ptr), 1);
	game->data.coinscltd = 0;
	game->data.mvcount = 1;
	ft_initimg(game);
	ft_map(game, av);
	return (1);
}

void	init_map(t_game *game, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	ft_calch(game, fd);
	close(fd);
	game->mapdata.mapalloc = 1;
	game->mapdata.row = malloc(sizeof(char *) * (game->mapdata.height + 1));
	if (!game->mapdata.row)
		return ;
}

int	main(int ac, char **av)
{
	t_game	game;

	game.mapdata.initgame = 0;
	game.img.initimg = 0;
	ft_check_av(ac, av);
	init_map(&game, av);
	ft_initgame(&game, av);
	mlx_hook(game.data.window, 17, 0, ft_close, &game);
	mlx_hook(game.data.window, KeyPress, KeyRelease, key_handlers, &game);
	mlx_loop_hook(game.data.mlx_ptr, display_exit, &game);
	mlx_loop(game.data.mlx_ptr);
	return (0);
}
