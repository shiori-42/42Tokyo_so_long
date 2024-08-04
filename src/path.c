/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:45:08 by syonekur          #+#    #+#             */
/*   Updated: 2024/08/03 22:55:20 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	allocate_visited_memory(t_game *game, char ***visited)
{
	int	y;

	*visited = malloc((game->map->y) * sizeof(char *));
	if (!*visited)
		return (1);
	y = 0;
	while (y < game->map->y)
	{
		(*visited)[y] = malloc((game->map->x + 1) * sizeof(char));
		if (!(*visited)[y])
		{
			free_double_pointer(*visited, y);
			return (1);
		}
		ft_memset((*visited)[y], '0', game->map->x + 1);
		y++;
	}
	return (0);
}

int	is_valid_path(t_game *game)
{
	char	**visited;
	int		exit_found;
	int		collectibles_found;
	int		y;

	visited = NULL;
	if (allocate_visited_memory(game, &visited))
		return (0);
	exit_found = (check_reachable_exit(game, game->player_x, game->player_y,
				visited));
	y = 0;
	while (y < game->map->y)
	{
		ft_memset(visited[y], '0', game->map->x);
		y++;
	}
	collectibles_found = count_reachable_collectibles(game, game->player_x,
			game->player_y, visited);
	free_double_pointer(visited, game->map->y);
	return (exit_found && collectibles_found == game->collectibles);
}
