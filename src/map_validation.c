/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:47:46 by syonekur          #+#    #+#             */
/*   Updated: 2024/08/21 13:26:03 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_borders(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (((y == 0) || (x == 0) || (y == game->map->height-1) || (x == game->map->width-1))
				&& game->map->map[y][x] != '1')
				handle_error(game,"Map borders must be covered by walls\n",1);
			x++;
		}
		y++;
	}
		printf("x:%d,y=%d",game->map->width,game->map->height);
		printf("x:%d,y=%d",x,y);
	return (0);
}

int	check_map_contents(t_game *game, int *player_cnt, int *exit_cnt,
		int *collected)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x <game->map->width)
		{
			if (game->map->map[y][x] == 'P')
				(*player_cnt)++;
			else if (game->map->map[y][x] == 'E')
				(*exit_cnt)++;
			else if (game->map->map[y][x] == 'C')
				(*collected)++;
			else if (game->map->map[y][x] != '0' && game->map->map[y][x] != '1')
				handle_error(game,"Invalid character in map",1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map_borders_and_contents(t_game *game)
{
	int	player_cnt;
	int	exit_cnt;
	int	collected;

	player_cnt = 0;
	exit_cnt = 0;
	collected = 0;
	if (game->map == NULL || game->map->map == NULL)
	{
		ft_putstr_fd("Error\nMap or map data is NULL\n", 2);
		return (1);
	}
	if (check_map_borders(game) || check_map_contents(game, &player_cnt,
			&exit_cnt, &collected))
		return (1);
	if (player_cnt != 1 || exit_cnt != 1 || collected < 1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Invalid number of players, exits, or collectibles\n", 2);
		return (1);
	}
	return (0);
}
