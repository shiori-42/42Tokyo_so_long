/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
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
	int		result;
	int		start_x;
	int		start_y;

	start_x = game->player_x;
	start_y = game->player_y;
	visited = NULL;
	if (allocate_visited_memory(game, &visited))
		return (1);
	result = (check_collectibles_path(game, start_x, start_y, visited)
			&& check_exit_path(game, start_x, start_y, visited));
	free_double_pointer(visited, game->map->y);
	return (result);
}
