/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:30:16 by shiori            #+#    #+#             */
/*   Updated: 2024/07/21 22:30:04 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_game *game, int x, int y, char **visited)
{
	return (y >= 0 && y < game->map->y && x >= 0 && x < game->map->x
		&& game->map->data[y][x] != '1' && visited[y][x] == '0');
}

int	check_valid_path(t_game *game, int x, int y, char **visited)
{
	int	directions[4][2];
	int	i;
	int	new_x;
	int	new_y;

	directions[0][0] = 0;
	directions[0][1] = 1;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = -1;
	directions[3][1] = 0;
	if (game->map->data[y][x] == 'E')
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

int	check_collectibles_path(t_game *game, int x, int y, char **visited)
{
	int	directions[4][2];
	int	i;
	int	new_x;
	int	new_y;

	directions[0][0] = 0;
	directions[0][1] = 1;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = -1;
	directions[3][1] = 0;
	if (game->map->data[y][x] == 'C')
		return (1);
	visited[y][x] = '1';
	i = 0;
	while (i < 4)
	{
		new_x = x + directions[i][0];
		new_y = y + directions[i][1];
		if (is_valid_move(game, new_x, new_y, visited)
			&& check_collectibles_path(game, new_x, new_y, visited))
			return (1);
		i++;
	}
	return (0);
}

int	check_current_path(t_game *game)
{
	char	**visited;
	int		result;
	int		start_x;
	int		start_y;

	visited = malloc((game->map->y + 1) * sizeof(char *));
	if (!visited)
		return (0);
	if (!check_current_path_part1(game, visited, &start_x, &start_y))
	{
		free(visited);
		return (0);
	}
	result = check_current_path_part2(game, visited, start_x, start_y);
	free_double_pointer(visited, game->map->y);
	return (result);
}
