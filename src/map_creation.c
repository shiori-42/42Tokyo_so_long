/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:32:45 by syonekur          #+#    #+#             */
/*   Updated: 2024/07/21 22:42:14 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_and_finalize_map(t_game *game, t_map *map, char *line, int *i)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len != map->x)
		handle_error(game, "Map has to be rectangular\n", 1);
	map->data[*i] = ft_strtrim(line, "\n");
	if (!map->data[*i])
		handle_error(game, "Memory allocation failed\n", 1);
	(*i)++;
	if (*i == map->y)
	{
		if (validate_map(map))
			handle_error(game, "Invalid map\n", 1);
	}
	return (0);
}
