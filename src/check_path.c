/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:30:16 by shiori            #+#    #+#             */
/*   Updated: 2024/08/03 21:11:00 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_game *game, int x, int y, char **visited)
{
	return (y >= 0 && y < game->map->y && x >= 0 && x < game->map->x
		&& game->map->data[y][x] != '1' && visited[y][x] == '0');
}

int	check_exit_path(t_game *game, int x, int y, char **visited)
{
	if (game->map->data[y][x] == 'E')
		return (1);
	visited[y][x] = '1';
	if (is_valid_move(game, x + 1, y, visited) && check_exit_path(game, x + 1,
			y, visited))
		return (1);
	if (is_valid_move(game, x - 1, y, visited) && check_exit_path(game, x - 1,
			y, visited))
		return (1);
	if (is_valid_move(game, x, y + 1, visited) && check_exit_path(game, x, y
			+ 1, visited))
		return (1);
	if (is_valid_move(game, x, y - 1, visited) && check_exit_path(game, x, y
			- 1, visited))
		return (1);
	return (0);
}

int	check_collectibles_path(t_game *game, int x, int y, char **visited)
{
	if (game->map->data[y][x] == 'C')
		return (1);
	visited[y][x] = '1';
	if (is_valid_move(game, x + 1, y, visited) && check_collectibles_path(game,
			x + 1, y, visited))
		return (1);
	if (is_valid_move(game, x - 1, y, visited) && check_collectibles_path(game,
			x - 1, y, visited))
		return (1);
	if (is_valid_move(game, x, y + 1, visited) && check_collectibles_path(game,
			x, y + 1, visited))
		return (1);
	if (is_valid_move(game, x, y - 1, visited) && check_collectibles_path(game,
			x, y - 1, visited))
		return (1);
	return (0);
}
