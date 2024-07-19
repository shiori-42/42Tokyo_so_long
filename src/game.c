/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:35:40 by shiori            #+#    #+#             */
/*   Updated: 2024/07/19 23:34:06 by syonekur         ###   ########.fr       */
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

void	init_game(t_game *game, t_map *map)
{
	int	x;
	int	y;

	load_img(game);
	game->map = map;
	game->collected = 0;
	game->collectibles = 0;
	game->move_cnt = 0;
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
				game->collectibles++;
			}
			x++;
		}
		y++;
	}
	write(1, "Player Start Position: (", 25);
	ft_putnbr_fd(game->player_x, 1);
	write(1, ", ", 2);
	ft_putnbr_fd(game->player_y, 1);
	write(1, ")\n", 2);
}

int	handle_keypress(int keycode, t_game *game)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_ESC)
		ft_exit(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		ft_move(game, 'y', -1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		ft_move(game, 'x', -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		ft_move(game, 'y', 1);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		ft_move(game, 'x', 1);
	if (game->map->data[game->player_y][game->player_x] == 'E'
		&& game->collected == game->collectibles)
		winner(game);
	return (0);
}

void	ft_move(t_game *game, char pos, int dir)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (pos == 'y')
		new_y += dir;
	else
		new_x += dir;
	if (game->map->data[new_y][new_x] != '1')
	{
		if (game->map->data[new_y][new_x] == 'C')
		{
			game->collected++;
			game->map->data[new_y][new_x] = '0';
		}
		game->map->data[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->map->data[new_y][new_x] = 'P';
		game->move_cnt++;
		write(1, "Moves: ", 7);
		ft_putnbr_fd(game->move_cnt, 1);
		write(1, "\n", 1);
		render_map(game);
	}
}

void	render_map(t_game *game)
{
	int		x;
	int		y;
	void	*img;

	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	y = 0;
	while (y < game->map->y)
	{
		x = 0;
		while (x < game->map->x)
		{
			if (game->map->data[y][x] == '1')
				img = game->img_wall;
			else if (game->map->data[y][x] == '0')
				img = game->img_empty;
			else if (game->map->data[y][x] == 'C')
				img = game->img_collectible;
			else if (game->map->data[y][x] == 'E')
				img = game->img_exit;
			else if (game->map->data[y][x] == 'P')
				img = game->img_player;
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x
				* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}


