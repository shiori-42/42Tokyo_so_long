/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/08/21 13:26:03 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_game *game)
{
	int	width;
	int	height;

	game->wall = mlx_xpm_file_to_image(game->mlx, WALL_XPM, &width,
			&height);
	game->tile = mlx_xpm_file_to_image(game->mlx, EMPTY_XPM, &width,
			&height);
	game->player = mlx_xpm_file_to_image(game->mlx, PLAYER_XPM,
			&width, &height);
	game->item = mlx_xpm_file_to_image(game->mlx,
			COLLECTIBLE_XPM, &width, &height);
	game->exit = mlx_xpm_file_to_image(game->mlx, EXIT_XPM, &width,
			&height);
	if (!game->wall || !game->tile || !game->player
		|| !game->item || !game->exit)
	{
		ft_putstr_fd("Error\nFailed to load textures\n", 2);
		free_resources(game);
		exit(EXIT_FAILURE);
	}
}

void	init_game(t_game *game)
{
	int	x;
	int	y;

	load_images(game);
	game->collected = 0;
	game->collectibles = 0;
	game->move_count = 0;
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map->map[y][x] == 'C')
			{
				game->collectibles++;
			}
		}
	}
}

void	ft_move(t_game *game, int new_x, int new_y)
{
	if (game->map->map[new_y][new_x] == '1')
		return ;
	if (game->map->map[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map->map[new_y][new_x] = '0';
	}
	if (game->map->map[new_y][new_x] == 'E')
	{
		if (game->collected == game->collectibles)
			winner(game);
		return ;
	}
	game->map->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map->map[new_y][new_x] = 'P';
	game->move_count++;
	ft_printf("Moves: %d\n", game->move_count);
	render_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == KEY_ESC || keycode == KEY_Q)
		ft_exit(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		new_x++;
	if (new_x != game->player_x || new_y != game->player_y)
		ft_move(game, new_x, new_y);
	return (0);
}

void	render_map(t_game *game)
{
	int		x;
	int		y;
	void	*image;

	mlx_clear_window(game->mlx, game->window);
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->map[y][x] == '1')
				image = game->wall;
			else if (game->map->map[y][x] == '0')
				image = game->tile;
			else if (game->map->map[y][x] == 'C')
				image = game->item;
			else if (game->map->map[y][x] == 'E')
				image = game->exit;
			else if (game->map->map[y][x] == 'P')
				image = game->player;
			mlx_put_image_to_window(game->mlx, game->window, image, x
				* TILE_SIZE, y * TILE_SIZE);
		}
	}
}
