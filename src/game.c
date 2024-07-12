/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/07/12 13:44:02 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "mlx.h"
#include "map.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void calculate_tile_size(t_game *game)
{
    int tile_width=game->window_width/game->map.x;
    int tile_height=game->window_height/game->map.y;
    if(tile_width<tile_height)
        game->tile_size=tile_width;
    else
        game->tile_size=tile_height;
}

void init_game(t_game *game) {
    int x;
    int y;

    int width;
    int height;
    game->move_cnt=0;
    calculate_tile_size(game);
    game->collect_item_cnt = 0;
    y = 0;
    while (y < game->map.y) {
        x = 0;
        while (x < game->map.x) {
            if (game->map.data[y][x] == 'P') {
                game->player_x = x;
                game->player_y = y;
            } else if (game->map.data[y][x] == 'C') {
                game->collect_item_cnt++;
            }
            x++;
        }
        y++;
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
    game->wall_texture=mlx_xpm_file_to_image(game->mlx,wall_xpm,&width, &height);
    game->empty_texture=mlx_xpm_file_to_image(game->mlx,empty_xpm,&width, &height);
    game->player_texture=mlx_xpm_file_to_image(game->mlx,player_xpm,&width, &height);
    game->items_texture=mlx_xpm_file_to_image(game->mlx,items_xpm,&width, &height);
    game->exit_texture=mlx_xpm_file_to_image(game->mlx,exit_xpm,&width, &height);
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
        game->map.data[game->player_y][game->player_x]='0';
        game->player_x=new_x;
        game->player_y=new_y;
        game->move_cnt++;
        printf("Moves: %d\n",game->move_cnt);
        render_map(game);
    }
    if(game->map.data[new_y][new_x]=='C')
        game->collect_item_cnt--;
    else if(game->map.data[new_y][new_x]=='E' && game->collect_item_cnt==0)
    {
        printf("Congratulations! You've completed the game in %d moves.\n", game->move_cnt);
        exit(0);
    }
    game->map.data[new_y][new_x]='P';
    render_map(game);
    return (0);
    
}


void render_map(t_game *game)
{   
    int x;
    int y;
    void *img;
    
    mlx_clear_window(game->mlx, game->win);
    y=0;
    while(y<game->map.y)
    {
        x=0;
        while(x<game->map.x)
        {
            if(game->map.data[y][x]=='1')
                img = game->wall_texture;
            else if(game->map.data[y][x]=='0')
                img = game->empty_texture;
            else if(game->map.data[y][x]=='C')
                img = game->items_texture;
            else if(game->map.data[y][x]=='E')
                img = game->exit_texture;
            else if(game->map.data[y][x]=='P')
                img = game->player_texture;
            else if(x==game->player_x && y==game->player_y)
                img=game->player_texture;
            mlx_put_image_to_window(game->mlx, game->win, img, x * game->tile_size, y * game->tile_size);
            x++;   
        }
        y++;
    }
    
}

