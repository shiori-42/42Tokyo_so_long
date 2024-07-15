/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:14:14 by syonekur          #+#    #+#             */
/*   Updated: 2024/07/15 19:39:28 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char	**data;
	int		x;
	int		y;
}			t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	int		window_width;
	int		window_height;
	int		tile_size;
	int		player_x;
	int		player_y;
	int		move_cnt;
	int		collected;
	void	*img_wall;
	void	*img_empty;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
}			t_game;

int			validate_map(t_map *map);
void		init_game(t_game *game);
t_map		read_map(const char *filename);
int			handle_keypress(int keycode, t_game *game);
int			on_destroy(t_game *game);
void		render_map(t_game *game);

#endif
