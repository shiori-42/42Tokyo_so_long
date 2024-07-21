/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:14:14 by syonekur          #+#    #+#             */
/*   Updated: 2024/07/21 18:26:08 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "../libft/includes/get_next_line.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img
{
	void	*player_up;
	void	*player_left;
	void	*player_right;
	void	*player_down;
	void	*background;
}			t_img;

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
	int		window_width;
	int		window_height;
	int		player_x;
	int		player_y;
	int		collected;
	int		collectibles;
	int		move_cnt;
	t_map	*map;
}			t_game;

# define WALL_XPM "assets/wall.xpm"
# define EMPTY_XPM "assets/empty.xpm"
# define PLAYER_XPM "assets/player.xpm"
# define COLLECTIBLE_XPM "assets/collectible.xpm"
# define EXIT_XPM "assets/exit.xpm"
# define TILE_SIZE 32
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

void		free_double_pointer(char **ptr, int height);
void		free_resources(t_game *game);
void		handle_error(t_game *game, char *str, int num);
int			ft_exit(t_game *game);
int			check_file_name(char *file_name);
int			cnt_map_size(char *filename, t_game *game, t_map *map);
int			validate_map(t_map *map);
int			create_map(char *filename, t_map *map);
void		init_game(t_game *game, t_map *map);
int			handle_keypress(int keycode, t_game *game);
void		render_map(t_game *game);
int			on_destroy(t_game *game);
int			check_current_path(t_game *game);
void		load_img(t_game *game);
void		ft_move(t_game *game, int new_x, int new_y);
void		winner(t_game *game);
void	free_map_data(char **data, int height);

#endif
