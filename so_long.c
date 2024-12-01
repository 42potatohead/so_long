/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:12:49 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/01 17:55:04 by zabu-bak         ###   ########.fr       */
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
int idle(t_game *game)
{
	void *spritesheet = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/chicken-32x32.xpm",
    &game->render.img_width, &game->render.img_height);


	int i = 0;
	int j = 1;
	while (i < 15000000)
	{
		if (i % 5620 == 0)
    	{
        	game->player.xpm_ptr = extract_sprite(game->data.mlx_ptr, spritesheet, (j++ % 5) * 32, 0);
        	if (!game->player.xpm_ptr)
        	{
            	ft_printf("Failed to extract sprite\n");
            	mlx_destroy_image(game->data.mlx_ptr, spritesheet);
            	return -1;
        	}
        	mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->player.xpm_ptr, 0, 0);
    	}
		i++;
	}

    mlx_destroy_image(game->data.mlx_ptr, spritesheet);
    return 0;
}

// int idle(t_game *game)
// {
// 	void *spritesheet = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/chicken-32x32.xpm",
//     &game->render.img_width, &game->render.img_height);


// 	int i = 0;
// 	int j = 1;
// 	while (i < 100)
//     {
//         game->player.xpm_ptr = extract_sprite(game->data.mlx_ptr, spritesheet, (j++ % 6) * 32, 0);
//         if (!game->player.xpm_ptr)
//         {
//             ft_printf("Failed to extract sprite\n");
//             mlx_destroy_image(game->data.mlx_ptr, spritesheet);
//             return -1;
//         }
//         mlx_put_image_to_window(game->data.mlx_ptr, game->data.window, game->player.xpm_ptr, 0, 0);
//         i++;
//     }

//     mlx_destroy_image(game->data.mlx_ptr, spritesheet);
//     return 0;
// }

void *extract_sprite(void *mlx_ptr, void *spritesheet, int x, int y)
{
    int sprite_width = 32;
    int sprite_height = 32;
    int bits_per_pixel;
    int src_size_line;
    int dst_size_line;
    int endian;

    void *sprite = mlx_new_image(mlx_ptr, sprite_width, sprite_height);
    if (!sprite)
        return NULL;

    char *src_data = mlx_get_data_addr(spritesheet, &bits_per_pixel, &src_size_line, &endian);
    char *dst_data = mlx_get_data_addr(sprite, &bits_per_pixel, &dst_size_line, &endian);

    int j = 0;
    while (j < sprite_height)
    {
        int i = 0;
        while (i < sprite_width)
        {
            int src_index = ((y + j) * src_size_line) + ((x + i) * (bits_per_pixel / 8));
            int dst_index = (j * dst_size_line) + (i * (bits_per_pixel / 8));
            memcpy(&dst_data[dst_index], &src_data[src_index], bits_per_pixel / 8);
            i++;
        }
        j++;
    }

    return sprite;
}

void ft_initimg(t_game *game)
{
	game->wall.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/FarmLand_Tile_1_.xpm",
		&game->render.img_height, &game->render.img_width);
	game->floor.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/Grass.xpm",
		&game->render.img_height, &game->render.img_width);
	// game->player.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/Chicken.xpm",
	// 	&game->render.img_height, &game->render.img_width);
	game->coins.xpm_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "./imgs/log.xpm",
		&game->render.img_height, &game->render.img_width);
}

int ft_initgame(t_game *game, char **av)
{
	// if(!ft_map(&game))
	// 	return(ft_printerr(), -1);
	game->data.mlx_ptr = mlx_init();
	if (!game->data.mlx_ptr)
		return (1);
	game->data.window = mlx_new_window(game->data.mlx_ptr, 400, 400, "WOW");
	if(!game->data.window)
		return (free(game->data.mlx_ptr), 1);
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
	mlx_loop_hook(game.data.mlx_ptr, idle, &game);
	mlx_loop(game.data.mlx_ptr);
	return (0);
}
