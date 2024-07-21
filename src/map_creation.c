/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:32:45 by syonekur          #+#    #+#             */
/*   Updated: 2024/07/21 21:50:34 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_map_line(t_map *map, char *line, int *i)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len != map->x)
	{
		ft_putstr_fd("Error\nMap has to be rectangular\n", 2);
		free(line);
		free_map_data(map->data, *i);
		return (1);
	}
	map->data[*i] = ft_strtrim(line, "\n");
	if (!map->data[*i])
	{
		free_map_data(map->data, *i);
		return (1);
	}
	(*i)++;
	return (0);
}

int	finalize_map(t_map *map, int i)
{
	if (i != map->y)
	{
		ft_putstr_fd("Error\nWrong number of map lines\n", 2);
		free_map_data(map->data, i);
		return (1);
	}
	return (validate_map(map));
}
