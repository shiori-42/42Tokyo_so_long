/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/07/10 21:28:38 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "mlx.h"
#include "map.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_game(t_game *game) {
    int x;
    int y;

    game->collect_item_cnt = 0;
    x = 0;
    while (x < game->map.x) {
        y = 0;
        while (y < game->map.y) {
            if (game->map.data[x][y] == 'P') {
                game->player_x = x;
                game->player_y = y;
            } else if (game->map.data[x][y] == 'C') {
                game->collect_item_cnt++;
            }
            y++;
        }
        x++;
    }
    if (game->mlx == NULL)
    {
        write(2, "Error: MLX initialization failed\n", 32);
        exit(1);
    }
    char *wall_xpm="textures/wall.xpm";
    char *empty_xpm="textures/empty.xpm";
    char *player_xpm="textures/player.xpm";
    char *items_xpm="textures/items.xpm";
    char *exit_xpm="textures/exit.xpm";
    game->wall_texture=mlx_xpm_file_to_image(game->mlx,wall_xpm,&x, &y);
    game->empty_texture=mlx_xpm_file_to_image(game->mlx,empty_xpm,&x, &y);
    game->player_texture=mlx_xpm_file_to_image(game->mlx,player_xpm,&x, &y);
    game->items_texture=mlx_xpm_file_to_image(game->mlx,items_xpm,&x, &y);
    game->exit_texture=mlx_xpm_file_to_image(game->mlx,exit_xpm,&x, &y);
    // if (!game->wall_texture || !game->empty_texture || !game->player_texture || !game->items_texture || !game->exit_texture)
    // {
    //     write(2, "Error: failed to load textures\n", 31);
    //     exit(1);
    // }
    if (!game->wall_texture)
    {
        write(2, "Error: failed to load wall\n", 31);
        exit(1);
    }
    if (!game->empty_texture)
    {
        write(2, "Error: failed to load empty\n", 31);
        exit(1);
    }
    if (!game->player_texture)
    {
        write(2, "Error: failed to load player\n", 31);
        exit(1);
    }
    if (!game->items_texture)
    {
        write(2, "Error: failed to load items\n", 31);
        exit(1);
    }
    if (!game->exit_texture)
    {
        write(2, "Error: failed to load exit\n", 31);
        exit(1);
    }
    render_map(game);
}




void render_map(t_game *game)
{   
    int x;
    int y;
    void *img;

    x=0;
    while(x<game->map.x)
    {
        y=0;
        while(y<game->map.y)
        {
            if(game->map.data[x][y]=='1')
                img = game->wall_texture;
            else if(game->map.data[x][y]=='0')
                img = game->empty_texture;
            else if(game->map.data[x][y]=='P')
                img = game->player_texture;
            else if(game->map.data[x][y]=='C')
                img = game->items_texture;
            else if(game->map.data[x][y]=='E')
                img = game->exit_texture;
            mlx_put_image_to_window(game->mlx, game->win, img, y * 32, x * 32);
            y++;   
        }
        x++;
    }
    
}

