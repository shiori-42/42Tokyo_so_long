/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:20:50 by shiori            #+#    #+#             */
/*   Updated: 2024/07/11 19:18:19 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H
#include <mlx.h>
#include "map.h"

typedef struct s_game {
    void    *mlx;
    void    *win;
    int     player_x;
    int     player_y;
    int     collect_item_cnt;
    void *wall_texture;	
    void *empty_texture;	
    void *player_texture;	
    void *items_texture;	
    void *exit_texture;
    int move_cnt;
    int window_width;
    int window_height;
    int     map_x;
    int     map_y;
    int tile_size;
    t_map   map;
} t_game;

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

void init_game(t_game *game);
void render_map(t_game *game);
int handle_keypress(int keycode,t_game *game);
void calculate_tile_size(t_game *game);

#endif
