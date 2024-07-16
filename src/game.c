/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/07/16 22:12:24 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_img(t_game *game)
{
	int	width;
	int	height;

	game->img_wall = mlx_xpm_file_to_image(game->mlx_ptr, WALL_XPM, &width,
			&height);
	game->img_empty = mlx_xpm_file_to_image(game->mlx_ptr, EMPTY_XPM, &width,
			&height);
	game->img_player = mlx_xpm_file_to_image(game->mlx_ptr, PLAYER_XPM, &width,
			&height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx_ptr,
			COLLECTIBLE_XPM, &width, &height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx_ptr, EXIT_XPM, &width,
			&height);
	if (!game->img_wall || !game->img_empty || !game->img_player
		|| !game->img_collectible || !game->img_exit)
	{
		write(2, "Error: Failed to load textures\n", 31);
		free_resources(game);
		exit(EXIT_FAILURE);
	}
}

void	free_resources(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx_ptr, game->img_wall);
	if (game->img_empty)
		mlx_destroy_image(game->mlx_ptr, game->img_empty);
	if (game->img_player)
		mlx_destroy_image(game->mlx_ptr, game->img_player);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx_ptr, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx_ptr, game->img_exit);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->map.data)
		free_double_pointer(game->map.data, game->map.y);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	init_game(t_game *game)
{
	int	x;
	int	y;

	game->window_width = game->map.x * TILE_SIZE;
	game->window_height = game->map.y * TILE_SIZE;
	game->collected = 0;
	y = 0;
	while (y < game->map.y)
	{
		x = 0;
		while (x < game->map.x)
		{
			if (game->map.data[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map.data[y][x] == 'C')
			{
				game->collected++;
			}
			x++;
		}
		y++;
	}
	printf("Player Start Position: (%d, %d)\n", game->player_x, game->player_y);
	if (!game->mlx_ptr)
	{
		write(2, "Error: MLX initialization failed\n", 32);
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->window_width,
			game->window_height, "So Long");
	if (!game->win_ptr)
	{
		write(2, "Error: Window creation failed\n", 31);
		free(game->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	load_img(game);
	render_map(game);
}


int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		new_y -= 1;
	if (keycode == 0)
		new_x -= 1;
	if (keycode == 1)
		new_y += 1;
	if (keycode == 2)
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
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x
				* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

int	on_destroy(t_game *game)
{
	free_resources(game);
	exit(0);
	return (0);
}
