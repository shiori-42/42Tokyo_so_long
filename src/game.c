/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/07/15 23:02:00 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	calculate_tile_size(t_game *game)
{
	int	tile_width;
	int	tile_height;

	tile_width = game->window_width / game->map.x;
	tile_height = game->window_height / game->map.y;
	if (tile_width < tile_height)
		game->tile_size = tile_width;
	else
		game->tile_size = tile_height;
}
void	load_img(t_game *game)
{
	wall_xpm = "assets/wall.xpm";
	empty_xpm = "assets/empty.xpm";
	player_xpm = "assets/player.xpm";
	collectible_xpm = "assets/collectible.xpm";
	exit_xpm = "assets/exit.xpm";
	game->img_wall = mlx_xpm_file_to_image(game->mlx_ptr, wall_xpm, &width,
			&height);
	game->img_empty = mlx_xpm_file_to_image(game->mlx_ptr, empty_xpm, &width,
			&height);
	game->img_player = mlx_xpm_file_to_image(game->mlx_ptr, player_xpm, &width,
			&height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx_ptr,
			collectible_xpm, &width, &height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx_ptr, exit_xpm, &width,
			&height);
	if (!game->img_wall || !game->img_empty || !game->img_player
		|| !game->img_collectible || !game->img_exit)
	{
		write(2, "Error: Failed to load textures\n", 31);
		exit(EXIT_FAILURE);
	}
}

void	ft_initialize(t_game *game, t_map *map)
{
	int	y;
	int	x;

	game->map = map;
	game->collected = 0;
	calculate_tile_size(game);
	y = 0;
	while (y < game->map->y)
	{
		x = 0;
		while (x < game->map->x)
		{
			if (game->map->data[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map->data[y][x] == 'C')
			{
				game->collected++;
			}
			x++;
		}
		y++;
	}
	if (!game->mlx_ptr)
	{
		write(2, "Error: MLX initialization failed\n", 32);
		exit(EXIT_FAILURE);
	}
	load_textures(game);
	render_map(game);
}
void	init_game(t_game *game)
{
	ft_initialize(game, game->map);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	printf("Key pressed: %d\n", keycode);
	if (keycode == 53)
		exit(0);
	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == 13) // W
		new_y -= 1;
	if (keycode == 0) // A
		new_x -= 1;
	if (keycode == 1) // S
		new_y += 1;
	if (keycode == 2) // D
		new_x += 1;
	if (game->map.data[new_y][new_x] != '1')
	{
		game->map.data[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->move_cnt++;
		printf("Moves: %d\n", game->move_cnt);
		render_map(game);
	}
	if (game->map.data[new_y][new_x] == 'C')
		game->collected--;
	else if (game->map.data[new_y][new_x] == 'E' && game->collected == 0)
	{
		printf("Congratulations! You've completed the game in %d moves.\n",
			game->move_cnt);
		exit(0);
	}
	game->map.data[new_y][new_x] = 'P';
	render_map(game);
	return (0);
}

void	render_map(t_game *game)
{
	int		x;
	int		y;
	void	*img;

	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	y = 0;
	while (y < game->map.y)
	{
		x = 0;
		while (x < game->map.x)
		{
			if (game->map.data[y][x] == '1')
				img = game->img_wall;
			else if (game->map.data[y][x] == '0')
				img = game->img_empty;
			else if (game->map.data[y][x] == 'C')
				img = game->img_collectible;
			else if (game->map.data[y][x] == 'E')
				img = game->img_exit;
			else if (game->map.data[y][x] == 'P')
				img = game->img_player;
			else if (x == game->player_x && y == game->player_y)
				img = game->img_player;
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x
				* game->tile_size, y * game->tile_size);
			x++;
		}
		y++;
	}
}

int	on_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(0);
	return (0);
}