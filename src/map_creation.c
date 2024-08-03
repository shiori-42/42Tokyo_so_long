/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:32:45 by syonekur          #+#    #+#             */
/*   Updated: 2024/08/03 18:29:06 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_and_store_map(t_game *game, char *line, int *i)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len != game->map->x)
		return (1);
	game->map->data[*i] = ft_strtrim(line, "\n");
	if (!game->map->data[*i])
		handle_error(game, "Failed map allocate process\n", 1);
	(*i)++;
	if (*i == game->map->y)
	{
		if (check_map_borders_and_contents(game->map))
			handle_error(game, "invalid map\n", 1);
	}
	return (0);
}
