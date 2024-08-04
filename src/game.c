/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/08/04 17:30:11 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_game *game)
{
	int	width;
	int	height;

	game->image_wall = mlx_xpm_file_to_image(game->mlx_ptr, WALL_XPM, &width,
			&height);
	game->image_empty = mlx_xpm_file_to_image(game->mlx_ptr, EMPTY_XPM, &width,
			&height);
	game->image_player = mlx_xpm_file_to_image(game->mlx_ptr, PLAYER_XPM,
			&width, &height);
	game->image_collectible = mlx_xpm_file_to_image(game->mlx_ptr,
			COLLECTIBLE_XPM, &width, &height);
	game->image_exit = mlx_xpm_file_to_image(game->mlx_ptr, EXIT_XPM, &width,
			&height);
	if (!game->image_wall || !game->image_empty || !game->image_player
		|| !game->image_collectible || !game->image_exit)
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
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->x)
		{
			if (game->map->data[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map->data[y][x] == 'C')
			{
				game->collectibles++;
			}
		}
	}
}

void	ft_move(t_game *game, int new_x, int new_y)
{
	if (game->map->data[new_y][new_x] == '1')
		return ;
	if (game->map->data[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map->data[new_y][new_x] = '0';
	}
	if (game->map->data[new_y][new_x] == 'E')
	{
		if (game->collected == game->collectibles)
			winner(game);
		else
			ft_exit(game);
		return ;
	}
	game->map->data[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map->data[new_y][new_x] = 'P';
	game->move_count++;
	write(1, "Moves: ", 7);
	ft_putnbr_fd(game->move_count, 1);
	write(1, "\n", 1);
	render_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == KEY_ESC)
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

	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->x)
		{
			if (game->map->data[y][x] == '1')
				image = game->image_wall;
			else if (game->map->data[y][x] == '0')
				image = game->image_empty;
			else if (game->map->data[y][x] == 'C')
				image = game->image_collectible;
			else if (game->map->data[y][x] == 'E')
				image = game->image_exit;
			else if (game->map->data[y][x] == 'P')
				image = game->image_player;
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, image, x
				* TILE_SIZE, y * TILE_SIZE);
		}
	}
}
