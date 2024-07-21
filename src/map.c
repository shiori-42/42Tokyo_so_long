/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/07/21 22:06:20 by syonekur         ###   ########.fr       */
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
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
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
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
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

int	validate_map(t_map *map)
{
	int	player_cnt;
	int	exit_cnt;
	int	collected;

	player_cnt = 0;
	exit_cnt = 0;
	collected = 0;
	if (map == NULL || map->data == NULL)
	{
		ft_putstr_fd("Error\nMap or map data is NULL\n", 2);
		return (1);
	}
	if (validate_map_borders(map) || validate_map_contents(map, &player_cnt,
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
