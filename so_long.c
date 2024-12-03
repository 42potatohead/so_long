/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:12:49 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/03 18:05:56 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_check_av(int ac, char **av)
{
	if(ac == 2)
	{
		char *last_char;
		last_char = ft_substr(av[1], (ft_strlen(av[1]) - 4), 4);
		if(ft_strncmp(".ber", last_char, 4))
			{
				ft_printf("Invalid file type, Please try again later. \n");
				free(last_char);
				exit (EXIT_FAILURE);
			}
		if(open(av[1], O_RDONLY) == -1)
			{
				ft_printf("File does not exist \n");
				free(last_char);
				exit (EXIT_FAILURE);
			}
		free(last_char);
	}
	else
	{
		ft_printf("wrong number arguments, Please try again later. \n");
		exit (EXIT_FAILURE);
	}
}

void ft_initimg(t_game *game)
{
	game->wall.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/FarmLand_Tile_1_.xpm",
		&game->render.img_height, &game->render.img_width);
	game->floor.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/Grass.xpm",
		&game->render.img_height, &game->render.img_width);
	game->player.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/ducky.xpm",
		&game->render.img_height, &game->render.img_width);
	game->coins.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/111.xpm",
		&game->render.img_height, &game->render.img_width);
}

int ft_initgame(t_game *game, char **av)
{
	game->data.mlx_ptr = mlx_init();
	if (!game->data.mlx_ptr)
		return (1);
	game->data.window = mlx_new_window(game->data.mlx_ptr, 400, 400, "WOW");
	if(!game->data.window)
		return (free(game->data.mlx_ptr), 1);
	game->data.coinscltd = 0;
	game->data.mvcount = 1;
	ft_initimg(game);
	ft_map(game, av);
	return (1);
}
int	main(int ac, char **av)
{
	t_game game;

	ft_check_av(ac, av);
	ft_initgame(&game, av);
	mlx_hook(game.data.window, 17, 0, ft_close, &game);
	mlx_hook(game.data.window, KeyPress, KeyRelease, key_handlers, &game);
	mlx_loop(game.data.mlx_ptr);
	return (0);
}
