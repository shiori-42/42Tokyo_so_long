/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:45:08 by syonekur          #+#    #+#             */
/*   Updated: 2024/07/21 21:49:59 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_current_path_part1(t_game *game, char **visited, int *start_x,
		int *start_y)
{
	int	y;

	*start_x = game->player_x;
	*start_y = game->player_y;
	y = 0;
	while (y < game->map->y)
	{
		visited[y] = malloc((game->map->x + 1) * sizeof(char));
		if (!visited[y])
		{
			free_double_pointer(visited, y);
			return (0);
		}
		y++;
	}
	return (1);
}

int	check_current_path_part2(t_game *game, char **visited, int start_x,
		int start_y)
{
	if (!visited)
	{
		return (0);
	}
	init_visited(visited, game->map->y, game->map->x);
	if (!check_collectibles_path(game, start_x, start_y, visited))
	{
		free_double_pointer(visited, game->map->y);
		return (0);
	}
	return (1);
}
