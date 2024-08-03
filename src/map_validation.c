/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:47:46 by syonekur          #+#    #+#             */
/*   Updated: 2024/08/03 17:33:48 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_borders(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (((y == 0) || (x == 0) || (y == map->y - 1) || (x == map->x - 1))
				&& map->data[y][x] != '1')
			{
				ft_putstr_fd("Error\nMap borders must be covered by walls\n",
					2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map_contents(t_map *map, int *player_cnt, int *exit_cnt,
		int *collected)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (map->data[y][x] == 'P')
				(*player_cnt)++;
			else if (map->data[y][x] == 'E')
				(*exit_cnt)++;
			else if (map->data[y][x] == 'C')
				(*collected)++;
			else if (map->data[y][x] != '0' && map->data[y][x] != '1')
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
