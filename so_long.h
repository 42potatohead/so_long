/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:55:24 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/19 12:30:02 by zabu-bak         ###   ########.fr       */
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
# define TILE_SIZE 42

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
	int			initimg;
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
	int			plyr_i;
	int			plyr_j;
	char		dir;
}				t_render;

typedef struct s_mapdata
{
	char		**row;
	char		**tmp_map;
	int			height;
	int			width;
	int			coins;
	int			exits;
	int			mapalloc;
	int			exit_j;
	int			exit_i;
	int			initgame;
	int			invalid;
	int			players;
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
	t_img		exit;
}				t_game;

int				key_handlers(int keycode, t_game *game);
int				ft_close(t_game *game, int code, char *msg);
void			ft_rendermap(t_game *game);
void			render_object(t_game *game, t_img img);
void			ft_identify_object(t_game *game);
void			ft_map(t_game *game, char **av);
void			render_player(t_game *game, int i, int j);
void			ft_playermove(t_game *game, int i, int j);
void			ft_movement(int keycode, t_game *game);
void			ft_checkmap(t_game *game);
void			ft_free_map(t_game *game);
void			win_game(t_game *game);
void			fill(t_game game, int j, int i, int *coll);
int				ft_checkpath(t_game game, int j, int i);
int				display_exit(t_game *game);
void			init_map(t_game *game, char **av);
void			ft_calch(t_game *game, int fd);

#endif
