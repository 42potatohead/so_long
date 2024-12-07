/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:55:24 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/07 19:56:23 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./X11/X.h"
# include "./X11/keysym.h"
# include "./libft/libft.h"
# include "./printf/ft_printf.h"
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>

typedef enum e_assets
{
	WALL = '1',
	FLOOR = '0',
	COINS = 'C',
	PLAYER = 'P'
}				t_assets;

typedef struct s_img
{
	void		*xpm_ptr;
}				t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*window;
	int			mvcount;
	int			coinscltd;
}				t_data;

typedef struct s_render
{
	int			img_width;
	int			img_height;
	int			i;
	int			j;
	int			player_i;
	int			player_j;
	char		dir;
}				t_render;

typedef struct s_mapdata
{
	char		**row;
	int			height;
	int			width;
	int			coins;
	int			exits;
	int			mapalloc;
}				t_mapdata;

typedef struct s_game
{
	t_data		data;
	t_render	render;
	t_mapdata	mapdata;
	t_img		img;
	t_img		wall;
	t_img		player;
	t_img		floor;
	t_img		coins;
}				t_game;

int				key_handlers(int keycode, t_game *game);
int				ft_close(t_game *game);
void			ft_rendermap(t_game *game);
void			render_object(t_game *game, t_img img);
void			ft_identify_object(t_game *game);
void			ft_map(t_game *game, char **av);
void			render_player(t_game *game, int i, int j);
void			ft_playermove(t_game *game, int i, int j);
void			ft_movement(int keycode, t_game *game);
void			ft_checkmap(t_game *game);
void			ft_free_map(t_game *game);
void win_game(t_game *game);
void fill(t_game game, int j, int i, int *coll);
int	ft_checkpath(t_game game, int j, int i);

#endif
