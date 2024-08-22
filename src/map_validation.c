/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:47:46 by syonekur          #+#    #+#             */
/*   Updated: 2024/08/22 18:34:15 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_borders(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (((y == 0) || (x == 0) || (y == game->map->height - 1)
					|| (x == game->map->width - 1))
				&& game->map->data[y][x] != '1')
				handle_error(game, "Map borders must be covered by walls\n");
			x++;
		}
		y++;
	}
}

void	check_map_contents(t_game *game, int *player_count, int *exit_count,
		int *items)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->data[y][x] == 'P')
				(*player_count)++;
			else if (game->map->data[y][x] == 'E')
				(*exit_count)++;
			else if (game->map->data[y][x] == 'C')
				(*items)++;
			else if (game->map->data[y][x] != '0'
				&& game->map->data[y][x] != '1')
				handle_error(game, "Invalid character in map\n");
			x++;
		}
		y++;
	}
}

void	check_map_borders_and_contents(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	item;

	player_count = 0;
	exit_count = 0;
	item = 0;
	check_map_borders(game);
	check_map_contents(game, &player_count, &exit_count, &item);
	if (player_count == 0)
		handle_error(game, "No player found on the map\n");
	else if (player_count > 1)
		handle_error(game, "Multiple players found on the map\n");
	if (exit_count == 0)
		handle_error(game, "No exit found on the map\n");
	else if (exit_count > 1)
		handle_error(game, "Multiple exits found on the map\n");
	if (item < 1)
		handle_error(game, "The map must contain at least one item\n");
}
