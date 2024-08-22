/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:30:16 by shiori            #+#    #+#             */
/*   Updated: 2024/08/22 16:05:19 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_game *game, int x, int y, char **visited)
{
	return (y >= 0 && y < game->map->height && x >= 0 && x < game->map->width
		&& game->map->data[y][x] != '1' && visited[y][x] == '0');
}

int	check_reachable_exit(t_game *game, int x, int y, char **visited)
{
	if (game->map->data[y][x] == 'E')
		return (1);
	visited[y][x] = '1';
	if (is_valid_move(game, x + 1, y, visited) && check_reachable_exit(game, x
			+ 1, y, visited))
		return (1);
	if (is_valid_move(game, x - 1, y, visited) && check_reachable_exit(game, x
			- 1, y, visited))
		return (1);
	if (is_valid_move(game, x, y + 1, visited) && check_reachable_exit(game, x,
			y + 1, visited))
		return (1);
	if (is_valid_move(game, x, y - 1, visited) && check_reachable_exit(game, x,
			y - 1, visited))
		return (1);
	return (0);
}

int	count_reachable_items(t_game *game, int x, int y, char **visited)
{
	int	count;

	count = 0;
	if (!is_valid_move(game, x, y, visited))
		return (0);
	visited[y][x] = '1';
	if (game->map->data[y][x] == 'C')
		count++;
	count += count_reachable_items(game, x + 1, y, visited);
	count += count_reachable_items(game, x - 1, y, visited);
	count += count_reachable_items(game, x, y + 1, visited);
	count += count_reachable_items(game, x, y - 1, visited);
	return (count);
}
