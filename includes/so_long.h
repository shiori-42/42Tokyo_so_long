/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:14:14 by syonekur          #+#    #+#             */
/*   Updated: 2024/07/16 19:50:30 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_WIDTH 16
# define TILE_HEIGHT 16

typedef struct s_map
{
	int		x;
	int		y;
	char	**data;
}			t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_wall;
	void	*img_empty;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
	int		tile_size;
	int		window_width;
	int		window_height;
	int		player_x;
	int		player_y;
	int		collected;
	int		move_cnt;
	t_map	map;
}			t_game;

# define WALL_XPM "assets/wall.xpm"
# define EMPTY_XPM "assets/empty.xpm"
# define PLAYER_XPM "assets/player.xpm"
# define COLLECTIBLE_XPM "assets/collectible.xpm"
# define EXIT_XPM "assets/exit.xpm"

void		free_double_pointer(char **ptr, int height);
void		free_resources(t_game *game);
void		handle_error(t_game *game, char *str, int num);
int			ft_exit(t_game *game);
void		check_file_name(char *file_name);
int			cnt_map_size(char *filename, t_map *map);
int			validate_map(t_map *map);
int			allocate_map_and_load(char *filename, t_map *map);
void		init_game(t_game *game);
void		calculate_tile_size(t_game *game);
int			handle_keypress(int keycode, t_game *game);
void		render_map(t_game *game);
int			on_destroy(t_game *game);
void		check_current_path(t_game *game);

#endif
