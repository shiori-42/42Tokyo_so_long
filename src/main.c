/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:51:47 by shiori            #+#    #+#             */
/*   Updated: 2024/07/10 20:53:51 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "game.h"


int main(void) {
    t_game game;

    game.mlx = mlx_init();
    if (game.mlx == NULL)
    {
        write(2, "Error: failed to initialize mlx\n", 32);	
        return (1);	
    }
    if (load_map("maps/map1.ber", &(game.map))!=0)
    {
        write(2, "Error: failed to load map\n", 26);
        exit(1);
    }
    if (validate_map(&(game.map))!=0)
    {
        write(2, "Error: invalid map\n", 19);
        exit(1);
    }
    game.win = mlx_new_window(game.mlx,game.map.y * 32, game.map.x * 32, "So Long");
    if (game.win == NULL)
    {
        write(2, "Error: failed to create window\n", 31);	
        return (1);
    }
    init_game(&game);
    mlx_loop(game.mlx);
    return (0);
}

