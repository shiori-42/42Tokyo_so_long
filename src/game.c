/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/07/10 22:55:48 by shiori           ###   ########.fr       */
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
            if (game->map.data[y][x] == 'P') {
                game->player_x = x;
                game->player_y = y;
            } else if (game->map.data[y][x] == 'C') {
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

int handle_keypress(int keycode,t_game *game)
{
    printf("Key pressed: %d\n", keycode); 
    int new_x;
    int new_y;
    if(keycode==53)
        exit(0);
    new_x=game->player_x;
    new_y=game->player_y;
    if(keycode==13) //W
        new_y-=1;
    if(keycode==0) //A
        new_x-=1;
    if(keycode==1) //S
        new_y+=1;
    if(keycode==2) //D
        new_x+=1;
    if(game->map.data[new_y][new_x]!='1')
    {
        game->player_x=new_x;
        game->player_y=new_y;
        render_map(game);
    }
    return (0);
    
}



void render_map(t_game *game)
{   
    int x;
    int y;
    void *img;
    int tile_size;
    
    tile_size = 32;
    x=0;
    while(x<game->map.x)
    {
        y=0;
        while(y<game->map.y)
        {
            if(game->map.data[y][x]=='1')
                img = game->wall_texture;
            else if(game->map.data[y][x]=='0')
                img = game->empty_texture;
            else if(game->map.data[y][x]=='C')
                img = game->items_texture;
            else if(game->map.data[y][x]=='E')
                img = game->exit_texture;
            else if(x==game->player_x && y==game->player_y)
                img=game->player_texture;
            mlx_put_image_to_window(game->mlx, game->win, img, x * tile_size, y * tile_size);
            y++;   
        }
        x++;
    }
    
}

