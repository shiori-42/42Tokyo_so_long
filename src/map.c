/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/07/21 18:43:09 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp((file_name + len - 4), ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nWrong file extension\n", 2);
		return (0);
	}
	return (1);
}

int	cnt_map_size(char *filename, t_game *game, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFailed to open file\n", 2);
		return (1);
	}
	map->x = 0;
	map->y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\n')
			map->y++;
		if (map->y == 1)
			map->x = ft_strlen(line) - 1;
		free(line);
	}
	close(fd);
	game->window_width = TILE_SIZE * map->x;
	game->window_height = TILE_SIZE * map->y;
	return (0);
}

int	validate_map(t_map *map)
{
	int	player_cnt;
	int	exit_cnt;
	int	collected;
	int	x;
	int	y;

	player_cnt = 0;
	exit_cnt = 0;
	collected = 0;
	if (map == NULL || map->data == NULL)
	{
		ft_putstr_fd("Error\nMap or map data is NULL\n", 2);
		return (1);
	}
	y = 0;
	while (y < map->y)
	{
		if (map->data[y] == NULL)
		{
			ft_putstr_fd("Error\nMap data row is NULL\n", 2);
			return (1);
		}
		if ((int)ft_strlen(map->data[y]) != map->x)
		{
			ft_putstr_fd("Error\nMap has to be rectangular\n", 2);
			return (1);
		}
		x = 0;
		while (x < map->x)
		{
			if (map->data[y][x] == 'P')
				player_cnt++;
			else if (map->data[y][x] == 'E')
				exit_cnt++;
			else if (map->data[y][x] == 'C')
				collected++;
			else if (map->data[y][x] != '0' && map->data[y][x] != '1')
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				return (1);
			}
			else if (((y == 0) || (x == 0) || (y == map->y - 1) || (x == map->x
						- 1)) && map->data[y][x] != '1')
			{
				ft_putstr_fd("Error\nMap borders must be covered by walls\n",
					2);
				return (1);
			}
			x++;
		}
		y++;
	}
	if (player_cnt != 1 || exit_cnt != 1 || collected < 1)
	{
		ft_putstr_fd("Error\nInvalid number of players, exits, or collectibles\n", 2);
		return (1);
	}
	return (0);
}

int	create_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		len;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		if (len != map->x)
		{
			ft_putstr_fd("Error\nMap has to be rectangular\n", 2);
			free(line);
			close(fd);
			free_map_data(map->data, i);
			return (1);
		}
		map->data[i] = ft_strtrim(line, "\n");
		free(line);
		if (!map->data[i])
		{
			close(fd);
			free_map_data(map->data, i);
			return (1);
		}
		i++;
	}
	close(fd);
	if (i != map->y)
	{
		ft_putstr_fd("Error\nWrong number of map lines\n", 2);
		free_map_data(map->data, i);
		return (1);
	}
	return (validate_map(map));
}
