/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:30:16 by shiori            #+#    #+#             */
/*   Updated: 2024/07/16 19:59:57 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_game *game, int x, int y, char **visited)
{
	return (y >= 0 && y < game->map.y && x >= 0 && x < game->map.x
		&& game->map.data[y][x] != '1' && visited[y][x] == '0');
}

int	check_valid_path(t_game *game, int x, int y, char **visited)
{
	int	directions[4][2]= {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int	i;
	int	new_x;
	int	new_y;

	if (game->map.data[y][x] == 'E')
		return (1);
	visited[y][x] = '1';
	i = 0;
	while (i < 4)
	{
		new_x = x + directions[i][0];
		new_y = y + directions[i][1];
		if (is_valid_move(game, new_x, new_y, visited) && check_valid_path(game,
				new_x, new_y, visited))
			return (1);
		i++;
	}
	return (0);
}

void	init_visited(char **visited, int height, int width)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			visited[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	check_current_path(t_game *game)
{
	int		start_x;
	int		start_y;
	char	**visited;
	int		y;

	start_x = game->player_x;
	start_y = game->player_y;
	visited = malloc(game->map.y * sizeof(char *));
	y = 0;
	while (y < game->map.y)
	{
		visited[y] = malloc(game->map.x * sizeof(char));
		y++;
	}
	init_visited(visited, game->map.y, game->map.x);
	if (!check_valid_path(game, start_x, start_y, visited))
	{
		free_double_pointer(visited, game->map.y);
		handle_error(game, "Error\nNo valid path exists\n", 1);
	}
	free_double_pointer(visited, game->map.y);
	render_map(game);
}
