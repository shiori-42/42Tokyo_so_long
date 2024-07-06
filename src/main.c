/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:51:47 by shiori            #+#    #+#             */
/*   Updated: 2024/07/06 20:51:48 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "game.h"

int main(void) {
    t_game game;

    game.mlx = mlx_init();
    if (game.mlx == NULL)
        return (1);
    game.win = mlx_new_window(game.mlx, 800, 600, "So Long");
    if (game.win == NULL)
        return (1);

    init_game(&game);

    mlx_loop(game.mlx);
    return (0);
}

