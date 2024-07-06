/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:20:50 by shiori            #+#    #+#             */
/*   Updated: 2024/07/06 21:20:51 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

typedef struct s_game {
    void    *mlx;
    void    *win;
    int     player_x;
    int     player_y;
    int     collect_item_cnt;
} t_game;

void init_game(t_game *game);

#endif
