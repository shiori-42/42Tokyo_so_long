/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:47:46 by syonekur          #+#    #+#             */
/*   Updated: 2024/08/22 16:18:30 by syonekur         ###   ########.fr       */
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

void	check_map_contents(t_game *game, int *player_cnt, int *exit_cnt,
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
				(*player_cnt)++;
			else if (game->map->data[y][x] == 'E')
				(*exit_cnt)++;
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
	int	player_cnt;
	int	exit_cnt;
	int	item;

	player_cnt = 0;
	exit_cnt = 0;
	item = 0;
	check_map_borders(game);
	check_map_contents(game, &player_cnt, &exit_cnt, &item);
	if (player_cnt != 1)
		handle_error(game, "Invalid number of players\n");
	if (exit_cnt != 1)
		handle_error(game, "Invalid number of exits\n");
	if (item < 1)
		handle_error(game, "Invalid number of items\n");
}
