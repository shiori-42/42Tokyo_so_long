/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:39:44 by syonekur          #+#    #+#             */
/*   Updated: 2024/08/21 23:40:26 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int			width;
	int			height;
	char		**data;
}				t_map;

typedef struct s_images
{
	void		*image_wall;
	void		*image_empty;
	void		*image_player;
	void		*image_collectible;
	void		*image_exit;
}				t_images;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			player_x;
	int			player_y;
	int			collected;
	int			collectibles;
	int			move_count;
	t_map		*map;
	t_images	*images;
}				t_game;

# define MAP_EXTENSION ".ber"
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
# define KEY_Q 113

void			free_double_pointer(char **ptr, int height);
void			free_string_array(char **ptr, int height);
void			free_resources(t_game *game);
void			handle_error(t_game *game, char *msg);
int				ft_exit(t_game *game);
void			check_file_name(char *file_name);
void			count_map_size(char *filename, t_game *game);
void			check_map_borders_and_contents(t_game *game);
void			create_map(t_game *game, char *filename);
void			init_game(t_game *game);
int				handle_keypress(int keycode, t_game *game);
void			render_map(t_game *game);
void			is_valid_path(t_game *game);
void			load_images(t_game *game);
void			ft_move(t_game *game, int new_x, int new_y);
void			winner(t_game *game);
void			check_map_borders(t_game *game);
void			check_map_contents(t_game *game, int *player_count,
					int *exit_count, int *collected);
int				is_valid_move(t_game *game, int x, int y, char **visited);
int				check_reachable_exit(t_game *game, int x, int y,
					char **visited);
int				count_reachable_collectibles(t_game *game, int x, int y,
					char **visited);
void			validate_and_store_map(t_game *game, char *line, int *i);
int				handle_expose(t_game *game);
int				close_handler(t_game *game);
void			free_map_data_until(char **data, int until);
void			map_data_util(t_game *game, char *line, int i);
char			*get_next_line_trimmed(int fd);

#endif