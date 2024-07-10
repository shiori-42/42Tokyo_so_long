/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:20:50 by shiori            #+#    #+#             */
/*   Updated: 2024/07/10 20:59:54 by shiori           ###   ########.fr       */
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
    t_map   map;
} t_game;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void init_game(t_game *game);
void render_map(t_game *game);

#endif
