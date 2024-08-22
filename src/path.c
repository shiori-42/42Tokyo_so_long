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

void	allocate_visited_memory(t_game *game, char ***visited)
{
	int	y;

	*visited = malloc(game->map->height * sizeof(char *));
	if (!*visited)
		handle_error(game, "Failed to allocate memory for visited array\n");
	y = 0;
	while (y < game->map->height)
	{
		(*visited)[y] = malloc(game->map->width * sizeof(char));
		if (!(*visited)[y])
		{
			free_double_pointer(*visited, y);
			handle_error(game, "Failed to allocate memory for visited row\n");
		}
		ft_memset((*visited)[y], '0', game->map->width);
		y++;
	}
}

void	is_valid_path(t_game *game)
{
	char	**visited;
	int		exit_found;
	int		items_found;
	int		y;

	visited = NULL;
	allocate_visited_memory(game, &visited);
	exit_found = check_reachable_exit(game, game->player_x, game->player_y,
			visited);
	y = 0;
	while (y < game->map->height)
	{
		ft_memset(visited[y], '0', game->map->width);
		y++;
	}
	items_found = count_reachable_items(game, game->player_x, game->player_y,
			visited);
	free_double_pointer(visited, game->map->height);
	if (!exit_found || items_found != game->items)
		handle_error(game, "No valid path or missing items\n");
}
