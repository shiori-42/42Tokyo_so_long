/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/07/06 21:29:49 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "map.h"
#include <unistd.h>
#include <stdlib.h>

void init_game(t_game *game) {
    t_map map;
    int x;
    int y;

    if (load_map("maps/map1.ber", &map) != 0) {
        write(2, "Error: failed to load map\n", 26);
        exit(1);
    }
    if (validate_map(&map) != 0) {
        write(2, "Error: invalid map\n", 19);
        exit(1);
    }
    game->collect_item_cnt = 0;
    x = 0;
    while (x < map.x) {
        y = 0;
        while (y < map.y) {
            if (map.data[x][y] == 'P') {
                game->player_x = x;
                game->player_y = y;
            } else if (map.data[x][y] == 'C') {
                game->collect_item_cnt++;
            }
            y++;
        }
        x++;
    }
}
