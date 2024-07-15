/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:14:14 by syonekur          #+#    #+#             */
/*   Updated: 2024/07/15 23:18:20 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_WIDTH 16
# define TILE_HEIGHT 16

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
	t_map	*map;
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
int			read_map(const char *filename, t_map *map);
int			handle_keypress(int keycode, t_game *game);
int			on_destroy(t_game *game);
void		render_map(t_game *game);
void		check_file_name(const char *file_name);
void		calculate_tile_size(t_game *game);
void		ft_initialize(t_game *game, t_map *map);
void		cnt_map_size(argv[1], &game->map);
int	allocate_map_and_load(&game->map);

#endif
